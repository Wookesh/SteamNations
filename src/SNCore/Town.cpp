#include "Town.hpp"

Town::Town(Tile *tile, const QString &name, QObject *parent): Object(tile, parent), name_(name)
{
	
}

Town::~Town()
{

}

void Town::updateAfter()
{

}

void Town::updateBefore()
{

}

QString Town::name() const
{
	return name_;
}

Unit *Town::createUnit(Prototype *)
{

}

void Town::getCaptured(Player *)
{

}
