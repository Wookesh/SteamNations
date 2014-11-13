#include "MoveAction.hpp"
#include "../Objects/Unit.hpp"

MoveAction::MoveAction(Unit *mainObject, Tile *tile): Action(mainObject, tile, Type::Move)
{
	
}

bool MoveAction::perform()
{
	return dynamic_cast<Unit *>(mainObject_)->move(tile_);
}

