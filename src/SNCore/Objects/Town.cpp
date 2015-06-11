#include "Town.hpp"
#include "Unit.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Console.hpp"
#include <Board.hpp>
#include <QDebug>
#include <QtAlgorithms>

#define GMlog() GameManager::get()->console()->in()

Town::Town(Tile *tile, Player *owner, const QString &name, QObject *parent) :
	Object(tile, ObjectType::Town, owner, parent), name_(name), population_(1),  
	food_(0), hasBuiltThisTurn_(0), capital_(false), capitalPlayer_(nullptr),
	baseFood_(3)
{
	owner->obtainTown(this);
	
	if (owner->capital() == nullptr) {
		owner->setCapital(this);
		capital_ = true;
		capitalPlayer_ = owner;
	}
	
	for (Tile *nTile : GameManager::get()->board()->getInRange(tile_, 1))
		if (nTile->localTown() == nullptr) {
			nTile->setLocalTown(this);
			townTiles_.push_back(nTile);
		}
	tile->setTown(this);
	setFoodGoal();
}

Town::~Town()
{
	if (tile_ != nullptr)
		tile_->setTown(nullptr);
	
	for (Tile *tile : townTiles_)
		tile->setLocalTown(nullptr);
	
	
	if (owner_ != nullptr)
		owner_->destroyTown(this);
}

void Town::setFoodGoal() {
	// Equation borrowed from Civ5 (almost, it's a bit different)
	foodGoal_ = qFloor(15 + 6 * (population_ - 1) + (population_ - 1) * (population_ - 1));
}

void Town::addNewTile() {
	Board *board = GameManager::get()->board();
	QVector<Tile *> possibleTiles = board->getSurroundings(this);
	GMlog() << "Possible " << possibleTiles.size() << " new tiles.\n";
	Tile *newTile = chooseBestTile(possibleTiles);
	
	if (newTile == nullptr)
		return;
	
	GMlog() << "Added new tile\n";
	townTiles_.push_back(newTile);
	newTile->setLocalTown(this);
	
	for (Tile *t : board->getNeighbours(newTile)) {
		t->setVisionState(owner_, VisionType::Visible);
	}
}

Tile *Town::chooseBestTile(QVector< Tile * > tiles) {
	if (tiles.empty())
		return nullptr;
	
	Tile *ret = nullptr;
	int value = -1;
	
	for (Tile *tile : tiles) {
		int weight = qMax((int) tile->resourceProduction() - 2 * (int) GameManager::get()->board()->getAbsoluteDistance(tile, tile_), 0);
		
		if (weight > value) {
			value = weight;
			ret = tile;
		}
	}
	
	return ret;
}


void Town::updateBefore() 
{
	for (Tile *tile : townTiles_) {
		tile->updateBefore();
		if (tile->resource() != Resource::None) {
			tile->gatherResource(this);
		}
		food_ += baseFood_;
	}
		
	if (food_ > foodGoal_) {
		GMlog() << "Food goal reached. Growing.\n";
		food_ = food_ - foodGoal_;
		++population_;
		setFoodGoal();
		addNewTile();
	}
	
	hasBuiltThisTurn_ = false;
}


QString Town::name() const
{
	return name_;
}

void Town::updateAfter()
{
	
}

void Town::addFood(SNTypes::amount food) {
	//GMlog() << "Added " << food << " food for total of " << food_ << "\n";
	food_ += food;
}


Unit *Town::createUnit(PrototypeType type)
{
	if (!canRecruit(type))
		return nullptr;
	
	owner_->removeResource(Resource::Gold, owner_->prototype(type)->cost());
	Unit *newUnit = owner_->createUnit(type, tile_);
	return newUnit;
}

void Town::getCaptured(Player *player)
{
	setOwner(player);
	player->obtainTown(this);
}

bool Town::canRecruit(PrototypeType type)
{
	if (tile_->unit() == nullptr &&
		GameManager::get()->currentPlayer() == owner() &&
		owner()->resource(Resource::Gold) >= owner()->prototype(type)->cost())
		return true;
	return false;
}

void Town::createBuilding (Tile *tile, Resource building) {
	tile->setBuilding(building);
	owner_->payForBuilding(building);
}

bool Town::canBuild (Tile *tile, Resource building) const {
	if (tile->localTown() != this)
		return false;
	
	if (tile->building() != Resource::None)
		return false;
	
	if (!owner_->canAffordBuilding(building))
		return false;
	
	if (hasBuiltThisTurn_)
		return false;
	
	return true;
}

bool Town::isCapital() const {
	return capital_;
}

SNTypes::population Town::population() const {
	return population_;
}

unsigned int Town::size() const {
	return townTiles_.size();
}

bool Town::save(QDataStream &out)
{
	out << name_ << population_ << food_ << foodGoal_ << hasBuiltThisTurn_ << capital_ << capitalPlayer_->name() << townTiles_.size();
	
	for (Tile *tile : townTiles_)
		out << tile->axial();
	
	return true;
}

bool Town::load(QDataStream &in)
{
	QString capitalPlayerName;
	int townTilesCount;
	in >> name_ >> population_ >> food_ >> foodGoal_ >> hasBuiltThisTurn_ >> capital_ >> capitalPlayerName >> townTilesCount;
	
	Player *player = GameManager::get()->player(capitalPlayerName);
	if (player == nullptr)
		return false;
	
	player->setCapital(this);
	capitalPlayer_ = player;
	
	townTiles_.clear();
	
	for (int i = 0; i < townTilesCount; ++i) {
		QPoint pos;
		in >> pos;
		Tile *tile = GameManager::get()->board()->getTileAxial(pos.x(), pos.y());
		if (tile != nullptr)
			townTiles_.push_back(tile);
		else 
			return false;
	}
	
	return true;
}

const QVector< Tile* >& Town::townTiles() const
{
	return townTiles_;
}
