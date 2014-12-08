#ifndef MOVEACTION_HPP
#define MOVEACTION_HPP

#include "Action.hpp"

class Unit;

class MoveAction : public Action {
public :
	MoveAction(Unit *mainObject, Tile *tile, unsigned int moveCost);
	virtual bool perform();
	unsigned int moveCost();
private:
	unsigned int moveCost_;
};


#endif