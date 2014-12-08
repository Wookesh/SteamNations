#include "SoldierPrototype.hpp"
#include "../Soldier.hpp"
#include "../../GameManager.hpp"


const QHash<PrototypeType, unsigned int> SoldierPrototype::ACTION_POINTS = {
	{PrototypeType::Infantry, 2},
	{PrototypeType::Heavy, 3},
	{PrototypeType::Artillery, 4}
};
const QHash<PrototypeType, unsigned int> SoldierPrototype::BASE_COST = {
	{PrototypeType::Infantry, 0},
	{PrototypeType::Heavy, 0},
	{PrototypeType::Artillery, 0}
};
const QHash<PrototypeType, QString> SoldierPrototype::BASE_NAME = {
	{PrototypeType::Infantry, "Infantry"},
	{PrototypeType::Heavy, "Heavy"},
	{PrototypeType::Artillery, "Artillery"}
};

SoldierPrototype::SoldierPrototype(PrototypeType type, const QString &name, int moveRange, int cost) :
	Prototype(type, name, moveRange, cost)
{
}

SoldierPrototype::SoldierPrototype(PrototypeType type) :
	Prototype(type, BASE_NAME[type], ACTION_POINTS[type], BASE_COST[type])
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
