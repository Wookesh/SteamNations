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

bool Soldier::canAttack(Tile *currTile)
{
	if ((GameManager::get()->currentPlayer() == owner()) &&
		(GameManager::get()->board()->getAbsoluteDistance(tile(), currTile) <= attackRange()) &&
		(currTile->unit() != nullptr) &&
		(currTile->unit()->owner() != owner()) &&
		(actionPointsLeft() >= attackCost()) &&
		(currTile->visionState(owner()) == VisionType::Visible)
		)
		return true;
	
	return false;
}

bool Soldier::attack(Unit *unit)
{
	if (canAttack(unit->tile())) {
		actionPointsLeft_ -= attackCost();
		unit->getAttacked(this);
		return true;
	}
	return false;
}

SNTypes::ap Soldier::attackCost() const
{
	return dynamic_cast<const SoldierPrototype *>(prototype_)->attackCost();
}

SNTypes::distance Soldier::attackRange() const
{
	return dynamic_cast<const SoldierPrototype *>(prototype_)->attackRange();
}

SNTypes::distance Soldier::ctrAtkRange() const
{
	return dynamic_cast<const SoldierPrototype *>(prototype_)->ctrAtkRange();
}

SNTypes::dmg Soldier::damage() const
{
	SNTypes::dmg baseDmg = dynamic_cast<const SoldierPrototype *>(prototype_)->damage();
	float hpModifier = (health() - healthLeft()) / health();
	float dmg = baseDmg * (1 - hpModifier * hpModifier);
	return qRound(dmg);
}

bool Soldier::canCapture(Tile *currTile)
{
	if ((GameManager::get()->currentPlayer() == owner()) &&
		(currTile->town() != nullptr) &&
		(currTile->town()->owner() != owner()) &&
		(currTile->unit() == nullptr) &&
		(currTile->visionState(owner()) == VisionType::Visible))
		return true;
	
	return false;
}

bool Soldier::capture(Town *town)
{
	if (canCapture(town->tile())) {
		town->setOwner(owner());
		return true;
	}
	return false;
}


float Soldier::attackBonus (Soldier *soldier) {
	return dynamic_cast<const SoldierPrototype *>(prototype_)->attackBonus(soldier->pType());
}


void Soldier::getAttacked(Soldier *soldier)
{
	SNTypes::dmg initialDmg = soldier->damage();
	float attackMultiplier = 0.2 // TODO: float GameManager::getAttackBonus(Player *, Player *) 
		+ soldier->attackBonus(this); 
	SNTypes::dmg finalDmg = qRound(attackMultiplier * initialDmg);
	
	bool counterAttak = GameManager::get()->board()->getAbsoluteDistance(tile_, soldier->tile_) <= ctrAtkRange();
	if (counterAttak) {
		SNTypes::dmg counterAttackDmg = damage();
		soldier->removeHealth(counterAttackDmg);
	}
	
	removeHealth(finalDmg);
}

