#include "Action.hpp"

Action::Action(Object *mainObject, Tile *tile, ActionType type) : type_(type), mainObject_(mainObject), tile_(tile)
{

}

Action::~Action()
{

}

const Tile *Action::tile() const
{
	return tile_;
}

ActionType Action::type() const
{
	return type_;
}

