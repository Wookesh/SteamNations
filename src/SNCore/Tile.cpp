#include "Tile.hpp"
#include "Objects/Town.hpp"
#include "Objects/Unit.hpp"
#include "GameManager.hpp"
#include "Board.hpp"
#include "Player.hpp"

Tile::Tile(unsigned int x_, unsigned int y_, Resource resource, int resourceProduction, TileType type, unsigned int weight) :
	town_(nullptr), localTown_(nullptr), unit_(nullptr), position_(x_, y_),
	resource_(resource), resourceProduction_(resourceProduction), produced_(0), weight_(weight), building_(Resource::None),
	tileType_(type)
{
	if (type == TileType::Random) {
		int i = qrand();
		switch(i % 11) {
			case 0:
				tileType_ = TileType::Desert;
				break;
				
			case 1:
				tileType_ = TileType::Field;
				break;
				
			case 2:
				tileType_ = TileType::Forest;
				break;
				
			case 3:
				tileType_ = TileType::Hill;
				break;
				
			case 4:
				tileType_ = TileType::Mountain;
				break;
				
			case 5:
				tileType_ = TileType::Jungle;
				break;
				
			case 6:
				tileType_ = TileType::Ruins1;
				break;
				
			case 7:
				tileType_ = TileType::Ruins2;
				break;
				
			case 8:
				tileType_ = TileType::Snow1;
				break;
				
			case 9:
				tileType_ = TileType::Snow2;
				break;
				
			case 10:
				tileType_ = TileType::Tundra;
				break;
		}
	}
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
	return ret;
}

void Tile::gatherResource(Town *town) {
	if (resource_ == Resource::Food) {
		town->addFood(takeResources());
	} else {
		town->owner()->addResource(resource_, takeResources());	
	}
}


/*
 * 	Returns movement cost of the tile. If it's not passable, weight should be less than 0.
 */
int Tile::weight() const {
	return weight_;
}

bool Tile::passable (const Player *player) const {
	if (weight_ < 0)
		return false;
	
	if (unit_ != nullptr && unit_->owner() != player)
		return false;
	
	if (town_ != nullptr && town_->owner() != player)
		return false;
		
	return true;
}

Resource Tile::building() const {
	return building_;
}

void Tile::setBuilding(Resource type) {
	building_ = type;
}

void Tile::addPlayerToVisionState(const Player *player) {
	visionState_.insert(player, VisionType::Invisible);
}

QMap< const Player*, VisionType > Tile::visionState() const {
	return visionState_;
}

VisionType Tile::visionState(const Player* player) const {
	return visionState_.value(player, VisionType::Invisible);
}


void Tile::setVisionState(const Player* player, VisionType visionType) {
	visionState_.insert(player, visionType);
}

bool Tile::visible(const Player *player) const {
	return visionState(player) == VisionType::Visible;
}

TileType Tile::tileType() const {
	return tileType_;
}
