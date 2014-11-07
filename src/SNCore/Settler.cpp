#include "Settler.hpp"
#include "SettlerPrototype.hpp"

Settler::Settler(Tile *tile, const SettlerPrototype *prototype, QObject *parent): Unit(tile, prototype, parent)
{

}

Settler::~Settler()
{

}

Town *Settler::createTown()
{
	return nullptr;
}

void Settler::getAttacked (Unit *) {
	
}
