#ifndef CREATEBUILDING_HPP
#define CREATEBUILDING_HPP

#include "Action.hpp"
#include "../Resources.hpp"

class Town;

class CreateBuildingAction : public Action {
public :
	CreateBuildingAction(Town *town, Tile *tile, Resource type);
	
	virtual bool perform();
private:
	Resource buildingType;
};


#endif