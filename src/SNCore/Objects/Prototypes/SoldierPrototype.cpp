#include "SoldierPrototype.hpp"
#include "../Soldier.hpp"
#include "../../GameManager.hpp"

const QString SoldierPrototype::BASE_NAME = QString("Soldier");

SoldierPrototype::SoldierPrototype(const QString &name, int moveRange, int cost) :
	Prototype(ProtoType::Soldier, name, moveRange, cost)
{
}

SoldierPrototype::~SoldierPrototype()
{

}

Unit *SoldierPrototype::createUnit(Tile *tile, Player *owner)
{
	Soldier *soldier = new Soldier(tile, this, owner);
	GameManager::get()->addObject(soldier->id(), soldier);
	return soldier;
}
