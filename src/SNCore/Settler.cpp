#include "Settler.hpp"
#include "SettlerPrototype.hpp"

Settler::Settler(const SettlerPrototype *prototype, QObject *parent): Unit(prototype, parent)
{

}

Settler::~Settler()
{

}

Town *Settler::createTown()
{
	return nullptr;
}
