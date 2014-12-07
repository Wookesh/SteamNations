#include "MoveAction.hpp"
#include "../Objects/Unit.hpp"

MoveAction::MoveAction(Unit *mainObject, Tile *tile, unsigned int moveCost): Action(mainObject, tile, ActionType::Move), moveCost_(moveCost)
{
	
}

bool MoveAction::perform()
{
	return dynamic_cast<Unit *>(mainObject_)->move(tile_, moveCost_);
}

unsigned int MoveAction::moveCost() {
	return moveCost_;
}


