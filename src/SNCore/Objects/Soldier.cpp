#include "Soldier.hpp"
#include "../Tile.hpp"
#include "Town.hpp"
#include "Prototypes/SoldierPrototype.hpp"
#include "../GameManager.hpp"
#include <Board.hpp>
#include <Player.hpp>

Soldier::Soldier(Tile* tile, const SoldierPrototype* prototype, Player *owner, QObject* parent): Unit(tile, prototype, owner, parent)
{

}

bool Soldier::canAttack(Tile* currTile)
{
	if ((GameManager::get()->currentPlayer() == owner()) &&
		(GameManager::get()->board()->getAbsoluteDistance(tile(), currTile) <= attackRange()) &&
		(currTile->unit() != nullptr) &&
		(currTile->unit()->owner() != owner()))
		return true;
	
	return false;
}

bool Soldier::attack(Unit* unit)
{
	if (canAttack(unit->tile())) {
		unit->getAttacked(this);
		return true;
	}
	return false;
}

SNTypes::distance Soldier::attackRange() const
{
	return dynamic_cast<const SoldierPrototype *>(prototype_)->attackRange();
}

SNTypes::dmg Soldier::damage() const
{
	SNTypes::dmg baseDmg = dynamic_cast<const SoldierPrototype *>(prototype_)->damage();
	double hpModifier = (health() - healthLeft()) / health();
	double dmg = baseDmg * (1 - hpModifier * hpModifier);
	return qRound(dmg);
}

bool Soldier::canCapture(Tile* currTile)
{	
	if((GameManager::get()->currentPlayer() == owner()) &&
		(currTile->town() != nullptr) &&
		(currTile->town()->owner() != owner()) &&
		(currTile->unit() == nullptr))
		return true;
	
	return false;
}
bool Soldier::capture(Town* town)
{
	if (canCapture(town->tile())) {
		town->setOwner(owner());
		return true;
	}
	return false;
}

void Soldier::removeHealth (SNTypes::dmg damage) 
{
	healthLeft_ = damage >= healthLeft_ ? 0 : healthLeft_ - damage;
	if (!healthLeft_) {
		owner_->destroyUnit(this);
	}
}

void Soldier::getAttacked(Soldier *soldier)
{
	SNTypes::dmg initialDmg = soldier->damage();
	double attackBonus = 0.2; // TODO: double GameManager::getAttackBonus(Player *, Player *) 
	SNTypes::dmg finalDmg = qRound(attackBonus * initialDmg);
	removeHealth(finalDmg);
	
	bool counterAttak = GameManager::get()->board()->getAbsoluteDistance(tile_, soldier->tile_) <= attackRange();
	if (counterAttak) {
		SNTypes::dmg counterAttackDmg = damage();
		soldier->removeHealth(counterAttackDmg);
	}
}

