#ifndef MOVEACTION_HPP
#define MOVEACTION_HPP

#include "Action.hpp"

class Unit;

class MoveAction : public Action {
public :
	MoveAction(Unit *mainObject, Tile *tile);
	
	virtual bool perform();
};


#endif