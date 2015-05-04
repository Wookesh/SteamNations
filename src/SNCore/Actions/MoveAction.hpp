#ifndef MOVE_ACTION_HPP
#define MOVE_ACTION_HPP

#include "Action.hpp"

class Unit;

class MoveAction : public Action {
public :
	MoveAction(Unit *mainObject, Tile *tile);
	virtual bool perform();
	unsigned int moveCost();
private:
	unsigned int moveCost_;
};


#endif