#include "Tile.hpp"
#include "Town.hpp"
#include "Unit.hpp"

Tile::Tile()
{

}

Tile::~Tile()
{

}

QList<const Object *> Tile::getObjects() const
{
	QList<const Object *> l;
	if (town_ != nullptr)
		l.push_back(town_);
	if (unit_ != nullptr)
		l.push_back(unit_);
	return l;
}

