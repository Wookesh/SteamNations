#include "Unit.hpp"
#include "Tile.hpp"
#include "Prototype.hpp"
#include "GameManager.hpp"
#include "Object.hpp"


Unit::Unit(Tile *tile, const Prototype *prototype, QObject *parent) : 
	Object(tile, Type::Unit, parent),
	prototype_(prototype),
	currentMoveRange_(prototype->moveRange())
{
}

Unit::~Unit()
{
	if (tile_ != nullptr)
		tile_->setUnit(nullptr);
}

void Unit::updateBefore() 
{

}

void Unit::updateAfter()
{
	currentMoveRange_ = moveRange();
}

QString Unit::name() const
{
	return prototype_->name();
}

quint8 Unit::moveRange() const
{
	return prototype_->moveRange();
}

quint8 Unit::currentMoveRange() const
{
	return currentMoveRange_;
}

bool Unit::canMove(const Tile *tile) const
{
	if (tile->unit() != nullptr && 
		GameManager::get()->board()->getAbsoluteDistance(tile, tile_) <= currentMoveRange())
		return true;
	return false;
}


bool Unit::move(Tile *tile)
{
	if (canMove(tile)) {
		tile_->setUnit(this);
		return true;
		emit positionChanged();
	}
	return false;
}

