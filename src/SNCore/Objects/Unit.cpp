#include "Unit.hpp"
#include "../Tile.hpp"
#include "Prototypes/Prototype.hpp"
#include "../GameManager.hpp"
#include "Object.hpp"
#include "Town.hpp"


Unit::Unit(Tile *tile, const Prototype *prototype, Player *owner, QObject *parent) :
    Object(tile, ObjectType::Unit, owner, parent),
	prototype_(prototype),
	currentMoveRange_(0)
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

ProtoType Unit::pType() const
{
	return prototype_->type();
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
	if (tile->unit() == nullptr && 
		GameManager::get()->board()->getAbsoluteDistance(tile, tile_) <= currentMoveRange() &&
		GameManager::get()->currentPlayer() == owner() &&
		(tile->town() == nullptr ? true : tile->town()->owner() == owner()))
		return true;
	return false;
}

bool Unit::move(Tile *tile)
{
	if (canMove(tile)) {
		currentMoveRange_ -= GameManager::get()->board()->getAbsoluteDistance(tile, tile_);
		tile_->setUnit(nullptr);
		tile->setUnit(this);
		setTile(tile);
		emit positionChanged();
		return true;
	}
	return false;
}

