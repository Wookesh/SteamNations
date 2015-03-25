#include "SettlerPrototype.hpp"
#include "../Settler.hpp"
#include "../../GameManager.hpp"
#include "../../Player.hpp"

const QString SettlerPrototype::BASE_NAME = QString("Settler");

SettlerPrototype::SettlerPrototype(const QString &name, SNTypes::ap actionPoints, SNTypes::amount cost, SNTypes::hp health, SNTypes::distance visionRange) :
	Prototype(PrototypeType::Settler, name, actionPoints, cost, health, visionRange)
{
}

SettlerPrototype::~SettlerPrototype()
{

}

Unit *SettlerPrototype::createUnit(Tile *tile, Player *owner)
{
	Settler *settler = new Settler(tile, this, owner);
	GameManager::get()->addObject(settler);
	return settler;
}
