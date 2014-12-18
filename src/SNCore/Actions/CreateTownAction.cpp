#include "CreateTownAction.hpp"
#include "Tile.hpp"
#include "../Objects/Town.hpp"
#include <GameManager.hpp>

CreateTownAction::CreateTownAction(Player *player, Tile *tile, const QString &name): 
	Action(nullptr, tile, ActionType::CreateTown), player_(player), name_(name)
{

}


bool CreateTownAction::perform()
{
	if (tile_->town() == nullptr) {
		Town *town = new Town(tile_, player_, name_);
		GameManager::get()->addObject(town);
		return true;
	}
	return false;
}
