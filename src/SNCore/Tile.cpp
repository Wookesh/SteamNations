#include "Tile.hpp"
#include "Objects/Town.hpp"
#include "Objects/Unit.hpp"

Tile::Tile(unsigned int x_, unsigned int y_, Resource resource, int resourceProduction, unsigned int weight) :
	town_(nullptr), localTown_(nullptr), unit_(nullptr), position_(x_, y_),
	resource_(resource), resourceProduction_(resourceProduction), produced_(0), weight_(weight)
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

int Tile::resourceProduction() const
{
	return resourceProduction_;
}

int Tile::takeResources()
{
	int ret = produced_;
	produced_ = 0;
	return ret;
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
