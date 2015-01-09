#include "SoldierPrototype.hpp"
#include "../Soldier.hpp"
#include "../../GameManager.hpp"
#include "SoldierStats.hpp"


const QHash<PrototypeType, SNTypes::ap> SoldierPrototype::ACTION_POINTS = {
	{PrototypeType::Infantry, INFANTRY_AP},
	{PrototypeType::Heavy, HEAVY_AP},
	{PrototypeType::Artillery, ARTILLERY_AP}
};

const QHash<PrototypeType, SNTypes::amount> SoldierPrototype::BASE_COST = {
	{PrototypeType::Infantry, INFANTRY_COST},
	{PrototypeType::Heavy, HEAVY_COST},
	{PrototypeType::Artillery, ARTILLERY_COST}
};

const QHash<PrototypeType, QString> SoldierPrototype::BASE_NAME = {
	{PrototypeType::Infantry, INFANTRY_NAME},
	{PrototypeType::Heavy, HEAVY_NAME},
	{PrototypeType::Artillery, ARTILLERY_NAME}
};

const QHash<PrototypeType, SNTypes::hp> SoldierPrototype::BASE_HEALTH = {
	{PrototypeType::Infantry, INFANTRY_HEALTH},
	{PrototypeType::Heavy, HEAVY_HEALTH},
	{PrototypeType::Artillery, ARTILLERY_HEALTH}
};

const QHash<PrototypeType, SNTypes::distance> SoldierPrototype::BASE_ATTACK_COST = {
	{PrototypeType::Infantry, INFANTRY_ATKCOST},
	{PrototypeType::Heavy, HEAVY_ATKCOST},
	{PrototypeType::Artillery, ARTILLERY_ATKCOST}
};

const QHash<PrototypeType, SNTypes::distance> SoldierPrototype::BASE_ATTACK_RANGE = {
	{PrototypeType::Infantry, INFANTRY_ATKRANGE},
	{PrototypeType::Heavy, HEAVY_ATKRANGE},
	{PrototypeType::Artillery, ARTILLERY_ATKRANGE}
};

const QHash<PrototypeType, SNTypes::hp> SoldierPrototype::BASE_DAMAGE = {
	{PrototypeType::Infantry, INFANTRY_DMG},
	{PrototypeType::Heavy, HEAVY_DMG},
	{PrototypeType::Artillery, ARTILLERY_DMG}
};

SoldierPrototype::SoldierPrototype(PrototypeType type, const QString &name,
	SNTypes::ap actionPoints,SNTypes::amount cost, SNTypes::hp health, 
	SNTypes::ap attackCost, SNTypes::distance attackRange, SNTypes::dmg damage) :
	Prototype(type, name, actionPoints, cost, health), 
	attackCost_(attackCost), 
	attackRange_(attackRange), 
	damage_(damage)
{
}

SoldierPrototype::SoldierPrototype(PrototypeType type) :
	Prototype(type, BASE_NAME[type], ACTION_POINTS[type], BASE_COST[type], BASE_HEALTH[type]),
	attackCost_(BASE_ATTACK_COST[type]), attackRange_(BASE_ATTACK_RANGE[type]), damage_(BASE_DAMAGE[type])
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

SNTypes::ap SoldierPrototype::attackCost() const 
{
	return attackCost_;
}

void SoldierPrototype::setAttackCost (SNTypes::ap attackCost) 
{
	attackCost_ = attackCost;
}


SNTypes::distance SoldierPrototype::attackRange() const
{
	return attackRange_;
}

void SoldierPrototype::setAttackRange(SNTypes::distance attackRange)
{
	attackRange_ = attackRange;
}


SNTypes::dmg SoldierPrototype::damage() const
{
	return damage_;
}

void SoldierPrototype::setDamage(SNTypes::dmg damage)
{
	damage_ = damage;
}


