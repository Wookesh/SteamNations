#ifndef SETTLEACTION_HPP
#define SETTLEACTION_HPP
#include "Action.hpp"

class Settler;

class SettleAction : public Action {
public :
	SettleAction(Settler *mainObject);
	
	virtual bool perform();
};

#endif