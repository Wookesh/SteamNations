#include "SettlerPrototype.hpp"
#include "Settler.hpp"

SettlerPrototype::SettlerPrototype(const QString &name, int moveRange, int cost) :
	Prototype(Type::Settler, name, moveRange, cost)
{

}

SettlerPrototype::~SettlerPrototype()
{

}

Unit *SettlerPrototype::createUnit(Tile *tile, Player *owner)
{
    Settler *settler = new Settler(tile, this, owner);
	return settler;
}
