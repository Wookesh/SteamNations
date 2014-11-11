#ifndef CREATEUNITACTION_HPP
#define CREATEUNITACTION_HPP
#include "Action.hpp"
#include "Prototype.hpp"

class Town;


class CreateUnitAction : public Action {
public:
	CreateUnitAction(Town *town, Prototype::Type type);
	
	virtual bool perform();
	Prototype::Type pType();
protected:
	Prototype::Type type_;
};


#endif