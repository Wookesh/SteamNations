#include "Soldier.hpp"
#include "../Tile.hpp"
#include "Town.hpp"
#include "Prototypes/SoldierPrototype.hpp"
#include "../GameManager.hpp"
#include <Board.hpp>

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
	return static_cast<const SoldierPrototype *>(prototype_)->attackRange();
}

SNTypes::dmg Soldier::damage() const
{
	return static_cast<const SoldierPrototype *>(prototype_)->damage();
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

void Soldier::getAttacked(Soldier *soldier)
{
	
}

