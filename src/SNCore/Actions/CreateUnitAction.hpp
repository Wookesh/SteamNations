#ifndef CREATE_UNIT_ACTION_HPP
#define CREATE_UNIT_ACTION_HPP

#include "Action.hpp"
#include "../Objects/Prototypes/Prototype.hpp"

class Town;

class CreateUnitAction : public Action {
public:
	CreateUnitAction(Town *town, PrototypeType type);
	
	virtual bool perform();
	PrototypeType pType();
protected:
	PrototypeType type_;
};


#endif