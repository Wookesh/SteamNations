#include "Tile.hpp"
#include "Objects/Town.hpp"
#include "Objects/Unit.hpp"
#include "GameManager.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "Player.hpp"

#define GMlog() GameManager::get()->console()->in()

const QVector<TileType> Tile::goldTiles = {
	TileType::Hill, TileType::Mountain
};

const QVector<TileType> Tile::foodTiles = {
	TileType::Field, TileType::Tundra, TileType::Forest
};

const QVector<TileType> Tile::researchTiles = {
	TileType::Jungle, TileType::Ruins1, TileType::Ruins2
};

const QVector<TileType> Tile::emptyTiles = {
	TileType::Desert, TileType::Snow1, TileType::Snow2
};

const QHash<Resource, QVector<TileType>> Tile::tileTypeMap = {
	{Resource::None, emptyTiles},
	{Resource::Gold, goldTiles},
	{Resource::Research, researchTiles},
	{Resource::Food, foodTiles}
};


Tile::Tile(unsigned int x_, unsigned int y_, Resource resource, int resourceProduction, unsigned int weight) :
	town_(nullptr), localTown_(nullptr), unit_(nullptr), position_(x_, y_),
	resource_(resource), resourceProduction_(resourceProduction), produced_(0), weight_(weight), building_(Resource::None),
	tileType_(TileType::Desert)
{
}

Tile::~Tile() 
{

}

QList<const Object *> Tile::getObjects() const 
{
	QList<const Object *> l;
	
	if (unit_ != nullptr) 
		l.push_back (unit_);
	
	if (town_ != nullptr) 
		l.push_back (town_);
	return l;
}

void Tile::updateBefore()
{
	produced_ = resourceProduction();
}

QPoint Tile::position() const 
{
	return position_;
}

QPoint Tile::axial() const 
{
	const int q = position_.x();
	const int r = position_.y();
	
	const int x = q;
	const int y = r - (q - (q & 1)) / 2;

	QPoint positionAxial(x, y);
	return positionAxial;
}

Town *Tile::town()
{
	return town_;
}

const Town *Tile::town() const
{
	return town_;
}

void Tile::setTown(Town *town)
{
	town_ = town;
}

Town *Tile::localTown()
{
	return localTown_;
}

const Town *Tile::localTown() const
{
	return localTown_;
}

void Tile::setLocalTown(Town *town)
{
	localTown_ = town;
}

Unit *Tile::unit()
{
	return unit_;
}

const Unit *Tile::unit() const
{
	return unit_;
}

void Tile::setUnit(Unit *unit)
{
	unit_ = unit;
}

Resource Tile::resource() const
{
	return resource_;
}

void Tile::setResource (Resource resource) {
	resource_ = resource;
}


int Tile::resourceProduction() const
{
	return resourceProduction_;
}

int Tile::takeResources()
{
	QVector<Tile *> neighbours = GameManager::get()->board()->getNeighbours(this);
	int bonus = 0;
	
	// Adequate building - 2 bonus resources
	if (building_ != Resource::None && building_ == resource_)
		bonus += 2;
	
	// Adjacent building of same type - 1 bonus resource
	for (Tile *tile : neighbours) {
		if (tile->town() == town_ && 
			tile->building() == building_ && 
			tile->building_ != Resource::None)
			++bonus;
	}
	
	int ret = produced_ + bonus;
	produced_ = 0;
	GMlog() << "Added " << ret << " resource of ";
	if (resource_ == Resource::Food)
		GMlog() << "Food\n";
	else if (resource_ == Resource::Gold) 
		GMlog() << "Gold\n";
	else if (resource_ == Resource::Research)
		GMlog() << "Research\n";
	return ret;
}

void Tile::gatherResource(Town *town) 
{
	float incomeMultiplier = 1. + town->owner()->bonusIncome();
	float bonusGold = 1. + town->owner()->bonusGold();
	
	if (resource_ == Resource::Food) {
		town->addFood(incomeMultiplier * takeResources());
	} else if (resource_ == Resource::Research) {
		town->owner()->addResource(resource_, incomeMultiplier * takeResources());
	} else if (resource_ == Resource::Gold) {
		town->owner()->addResource(resource_, bonusGold * incomeMultiplier * takeResources());
	}
}


/**
 * Returns movement cost of the tile. If it's not passable, weight should be less than 0.
 */
int Tile::weight() const 
{
	return weight_;
}

bool Tile::passable (const Player *player) const 
{
	if (weight_ < 0)
		return false;
	
	if (unit_ != nullptr && unit_->owner() != player)
		return false;
	
	return true;
}

Resource Tile::building() const 
{
	return building_;
}

void Tile::setBuilding(Resource type) 
{
	building_ = type;
}

void Tile::addPlayerToVisionState(const Player *player) 
{
	visionState_.insert(player, VisionType::Invisible);
}

QMap< const Player*, VisionType > Tile::visionState() const 
{
	return visionState_;
}

VisionType Tile::visionState(const Player* player) const 
{
	return visionState_.value(player, VisionType::Invisible);
}


void Tile::setVisionState(const Player* player, VisionType visionType) 
{
	visionState_.insert(player, visionType);
}

bool Tile::visible(const Player *player) const 
{
	return visionState(player) == VisionType::Visible;
}

TileType Tile::tileType() const 
{
	return tileType_;
}

bool Tile::load(QDataStream &in)
{
	in >> resource_ >> resourceProduction_ >> tileType_ >> produced_ >> weight_ >> building_;
	
	for (Player *player: GameManager::get()->players())
		addPlayerToVisionState(player);
	for (int i = 0; i < GameManager::get()->players().size(); ++i) {
		QString playerName;
		VisionType vision = VisionType::Invisible;
		in >> playerName >> vision;
		Player *player = GameManager::get()->player(playerName);
		if (player == nullptr)
			return false;
		visionState_.insert(player, vision);
	}
	return true;
}

bool Tile::save(QDataStream &out)
{
	out << resource_ << resourceProduction_ << tileType_ << produced_ << weight_ << building_;
	
	for (const Player *player: visionState_.keys())
		out << player->name() << visionState_.value(player, VisionType::Invisible);
	return true;
}

void Tile::setTileType() {
	int i = qrand() % tileTypeMap[resource_].length();
	tileType_ = tileTypeMap[resource_][i];
}