#ifndef ATTACKACTION_HPP
#define ATTACKACTION_HPP
#include "Action.hpp"
class Unit;
class Soldier;

class AttackAction : public Action {
public:
	AttackAction(Soldier *mainObject, Unit *target);
	
	virtual bool perform();
protected:
	Unit *target_;
};


#endif