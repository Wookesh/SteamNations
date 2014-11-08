#include "Action.hpp"

Action::Action(Object *mainObject, Tile *tile, Type type) : type_(type), mainObject_(mainObject), tile_(tile)
{

}

Action::~Action()
{

}


const Tile *Action::tile() const
{
	return tile();
}

Action::Type Action::type() const
{
	return type_;
}

