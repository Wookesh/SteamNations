#include "SettlerPrototype.hpp"
#include "Settler.hpp"
#include "GameManager.hpp"

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
	GameManager::get()->addObject(settler->id(), settler);
	return settler;
}
