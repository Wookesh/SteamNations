#include "../Player.hpp"
#include "Town.hpp"
#include "../Tile.hpp"
#include "Unit.hpp"
#include <QDebug>

Town::Town(Tile *tile, Player *owner, const QString &name, QObject *parent): Object(tile, Type::Town, owner, parent), name_(name)
{
	
}

Town::~Town()
{
	if (tile_ != nullptr)
		tile_->setTown(nullptr);
}

void Town::updateBefore() 
{

}


QString Town::name() const
{
	return name_;
}

void Town::updateAfter()
{
	
}

Unit *Town::createUnit(Prototype::Type type)
{
	Unit *newUnit = owner_->createUnit(type, tile_);
	return newUnit;
}

void Town::getCaptured(Player *player)
{
	player->obtainTown(this);
}

bool Town::canRecruit(Prototype::Type type)
{
	return tile_->unit() == nullptr;
}
