#include "Soldier.hpp"
#include "SNCore/Tile.hpp"
#include "Town.hpp"
#include "Prototypes/SoldierPrototype.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/AI/AI.hpp"
#include "SNCore/Console.hpp"

Soldier::Soldier(Tile* tile, const SoldierPrototype* prototype, Player *owner, QObject* parent):
	Unit(tile, prototype, owner, AI::soldierHeuristic, parent)
{

}

bool Soldier::canAttack(const Tile *currTile) const
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

bool Soldier::canCapture(const Tile *currTile) const
{
	if ((GameManager::get()->currentPlayer() == owner()) &&
		(currTile->town() != nullptr) &&
		(currTile->town()->owner() != owner()) &&
		(currTile->unit() == nullptr) &&
		(currTile->visionState(owner()) == VisionType::Visible) &&
		actionPointsLeft_ >= GameManager::get()->board()->getDistance(tile_, currTile) &&
		GameManager::get()->board()->getDistance(tile_, currTile) >= 1)
		return true;
	
	return false;
}

bool Soldier::capture(Town *town, unsigned int captureCost)
{
	if (canCapture(town->tile())) {
		town->setOwner(owner());
		
		if (town->isCapital())
			GameManager::get()->checkIfWin(owner_, WinCondition::Conquest);
		
		spentActionPoints(captureCost);
		tile_->setUnit(nullptr);
		town->tile()->setUnit(this);
		setTile(town->tile());
		updateVision();
		emit positionChanged();
		
		return true;
	}
	return false;
}

bool Soldier::canPerform(ActionType action, const Tile *tile) const
{
	if (action == ActionType::Capture)
		return canCapture(tile);
	if (action == ActionType::Attack)
		return canAttack(tile);
	return Unit::canPerform(action, tile);
}

float Soldier::attackBonus (Soldier *soldier) 
{
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

ActionType Soldier::getActionType(Tile *tile)
{
	if (tile->unit())
		return ActionType::Attack;
	if (tile->town())
		return ActionType::Capture;
	return ActionType::Move;
}


void Soldier::updateBefore() {
	actionPointsLeft_ = actionPoints();
	if (owner_->hasBonus(BonusType::Def, 2) &&
		health() > healthLeft_ &&
		tile()->localTown() != nullptr &&
		tile()->localTown()->owner() == owner_) {
			++healthLeft_;
	}
}