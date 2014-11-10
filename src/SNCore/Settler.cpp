#include "Settler.hpp"
#include "SettlerPrototype.hpp"

Settler::Settler(Tile *tile, const SettlerPrototype *prototype, QObject *parent): Unit(tile, prototype, parent)
{

}

Settler::~Settler()
{

}

bool Settler::canSettle() const
{
	return false;
}

bool Settler::settle()
{
	return canSettle();
}


Town *Settler::createTown()
{
	return nullptr;
}

void Settler::getAttacked (Unit *) {
	
}
