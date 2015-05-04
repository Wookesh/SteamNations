#include "MoveAction.hpp"
#include "../Objects/Unit.hpp"
#include "GameManager.hpp"
#include <Board.hpp>

MoveAction::MoveAction(Unit *mainObject, Tile *tile): Action(mainObject, tile, ActionType::Move)
{
	moveCost_ = GameManager::get()->board()->getDistance(mainObject_->tile(), tile);
}

bool MoveAction::perform()
{
	return dynamic_cast<Unit *>(mainObject_)->move(tile_, moveCost_);
}

unsigned int MoveAction::moveCost() {
	return moveCost_;
}


