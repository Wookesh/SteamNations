#include "CreateBuildingAction.hpp"
#include "../Objects/Town.hpp"

CreateBuildingAction::CreateBuildingAction(Town *town, Tile *tile, Resource type) : 
	Action (town, tile, ActionType::CreateBuilding),
	buildingType(type)
	{

}

bool CreateBuildingAction::perform() {
	Town *town = dynamic_cast<Town*>(mainObject_);
	
	if (town->canBuild(tile_, buildingType)) {
		town->createBuilding(tile_, buildingType);
		return true;
	} else 
		return false;
}

