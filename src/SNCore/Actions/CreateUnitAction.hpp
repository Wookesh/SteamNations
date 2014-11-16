#ifndef CREATEUNITACTION_HPP
#define CREATEUNITACTION_HPP
#include "Action.hpp"
#include "../Objects/Prototypes/Prototype.hpp"

class Town;


class CreateUnitAction : public Action {
public:
	CreateUnitAction(Town *town, ProtoType type);
	
	virtual bool perform();
	ProtoType pType();
protected:
	ProtoType type_;
};


#endif