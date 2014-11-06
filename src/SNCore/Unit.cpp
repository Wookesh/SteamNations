#include "Unit.hpp"

Unit::Unit(const Prototype *prototype, QObject *parent) : Object(parent), prototype_(prototype)
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

bool Unit::move(Tile *tile)
{
	// Placeholder
	return false;
}

