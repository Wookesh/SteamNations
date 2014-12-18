#include "SpawnUnitAction.hpp"
#include <Tile.hpp>
#include <Player.hpp>

SpawnUnitAction::SpawnUnitAction(Player *player, Tile *tile, const PrototypeType &type):
	Action(nullptr, tile, ActionType::SpawnUnit), player_(player), type_(type)
{

}


bool SpawnUnitAction::perform()
{
	if (tile_->unit() != nullptr || !tile_->passable(player_))
		return false;
	
	player_->createUnit(type_, tile_);
	return true;
}
