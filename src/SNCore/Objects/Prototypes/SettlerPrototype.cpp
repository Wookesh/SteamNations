#include "SettlerPrototype.hpp"
#include "../Settler.hpp"
#include "../../GameManager.hpp"
#include "../../Player.hpp"

const QString SettlerPrototype::BASE_NAME = QString("Settler");

SettlerPrototype::SettlerPrototype(const QString &name, int moveRange, int cost) :
	Prototype(ProtoType::Settler, name, moveRange, cost)
{
}

SettlerPrototype::~SettlerPrototype()
{

}

Unit *SettlerPrototype::createUnit(Tile *tile, Player *owner)
{
	Settler *settler = new Settler(tile, this, owner);
	GameManager::get()->addObject(settler->id(), settler);
	QObject::connect(settler, &Settler::townCreated, GameManager::get(), &GameManager::checkIfWin);
	return settler;
}
