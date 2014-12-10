#include "SoldierPrototype.hpp"
#include "../Soldier.hpp"
#include "../../GameManager.hpp"


const QHash<PrototypeType, SNTypes::ap> SoldierPrototype::ACTION_POINTS = {
	{PrototypeType::Infantry, 2},
	{PrototypeType::Heavy, 3},
	{PrototypeType::Artillery, 4}
};

const QHash<PrototypeType, SNTypes::amount> SoldierPrototype::BASE_COST = {
	{PrototypeType::Infantry, 0},
	{PrototypeType::Heavy, 0},
	{PrototypeType::Artillery, 0}
};

const QHash<PrototypeType, QString> SoldierPrototype::BASE_NAME = {
	{PrototypeType::Infantry, "Infantry"},
	{PrototypeType::Heavy, "Heavy"},
	{PrototypeType::Artillery, "Artillery"}
};

const QHash<PrototypeType, SNTypes::hp> SoldierPrototype::BASE_HEALTH = {
	{PrototypeType::Infantry, 20},
	{PrototypeType::Heavy, 35},
	{PrototypeType::Artillery, 30}
};

SoldierPrototype::SoldierPrototype(PrototypeType type,
	const QString &name, SNTypes::ap actionPoints,SNTypes::amount cost, SNTypes::hp health) :
	Prototype(type, name, actionPoints, cost, health)
{
}

SoldierPrototype::SoldierPrototype(PrototypeType type) :
	Prototype(type, BASE_NAME[type], ACTION_POINTS[type], BASE_COST[type], BASE_HEALTH[type])
{
}

SoldierPrototype::~SoldierPrototype()
{

}

Unit *SoldierPrototype::createUnit(Tile *tile, Player *owner)
{
	Soldier *soldier = new Soldier(tile, this, owner);
	GameManager::get()->addObject(soldier);
	return soldier;
}
