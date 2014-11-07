#include "Unit.hpp"
#include "Tile.hpp"
#include "Prototype.hpp"

Unit::Unit(Tile *tile, const Prototype *prototype, QObject *parent) : Object(tile, parent), prototype_(prototype)
{
}

Unit::~Unit()
{
	if (tile_ != nullptr)
		tile_->setUnit(nullptr);
}

void Unit::updateBefore() {

}

void Unit::updateAfter()
{
	
}

QString Unit::name() const
{
	return prototype_->name();
}


bool Unit::move(Tile *tile)
{
	// Placeholder
	return false;
}

