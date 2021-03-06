#include "Settler.hpp"
#include "Prototypes/SettlerPrototype.hpp"
#include "Town.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/AI/AI.hpp"
#include <QDebug>

Settler::Settler(Tile *tile, const SettlerPrototype *prototype, Player *owner, QObject *parent):
	Unit(tile, prototype, owner, AI::settlerHeuristic, parent)
{
	if (ComputerPlayer *cp = dynamic_cast<ComputerPlayer *>(owner)) 
		cp->setLastTimeSettlerBought(GameManager::get()->currentTurn());
}

Settler::~Settler()
{
	if (tile_ != nullptr)
		tile_->setUnit(nullptr);
	
	if (owner_ != nullptr)
		owner_->destroyUnit(this);
}

bool Settler::canSettle(const Tile *tile) const
{
	if (tile == tile_ && tile->town() == nullptr 
		&& tile->localTown() == nullptr
		&& GameManager::get()->currentPlayer() == owner_)
		return true;
	return false;
}

bool Settler::settle()
{
	if (!canSettle(tile_))
		return false;
	
	Town *town = createTown();
	
	if (owner()->capital() == nullptr) {
		owner()->setCapital(town);
		emit capitalCreated(owner_);
	}
	emit townCreated(owner_);
	
	return true;
}

bool Settler::canPerform(ActionType action, const Tile *tile) const
{
	if (action == ActionType::Settle)
		return canSettle(tile);
	return Unit::canPerform(action, tile);
}

Town *Settler::createTown()
{
	Town * town = new Town(tile_, owner_);
	GameManager::get()->addObject(town);
	tile_->setTown(town);
	return town;
}

void Settler::getAttacked(Soldier *) 
{
	removeHealth(healthLeft());
}

ActionType Settler::getActionType(Tile *tile)
{
	if (!tile->visible(owner()))
		return ActionType::Move;
	return ActionType::Settle;
}

int Settler::turnWithoutSettle() const
{
	return turnWithoutSettle_;
}

void Settler::updateAfter()
{
	Unit::updateAfter();
	++turnWithoutSettle_;
}
