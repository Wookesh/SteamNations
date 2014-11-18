#include "SettlerPrototype.hpp"
#include "../Settler.hpp"
#include "../../GameManager.hpp"

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
	QObject::connect(settler, SIGNAL(townCreated(Player *)),
					 GameManager::get(), SLOT(checkIfWin(Player*))
	);
	return settler;
}
