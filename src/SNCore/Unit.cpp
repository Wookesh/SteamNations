#include "Unit.hpp"
#include "Prototype.hpp"

Unit::Unit(Tile *tile, const Prototype *prototype, QObject *parent) : Object(tile, parent), prototype_(prototype)
{
}

Unit::~Unit()
{
	
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

