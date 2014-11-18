#include "../Player.hpp"
#include "Town.hpp"
#include "../Tile.hpp"
#include "Unit.hpp"
#include "../GameManager.hpp"
#include <QDebug>

Town::Town(Tile *tile, Player *owner, const QString &name, QObject *parent) :
	Object(tile, ObjectType::Town, owner, parent), name_(name)
{
	owner->obtainTown(this);
}

Town::~Town()
{
	if (tile_ != nullptr)
		tile_->setTown(nullptr);
	
	if (owner_ != nullptr)
		owner_->destroyTown(this);
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

Unit *Town::createUnit(ProtoType type)
{
	Unit *newUnit = owner_->createUnit(type, tile_);
	return newUnit;
}

void Town::getCaptured(Player *player)
{
	setOwner(player);
	player->obtainTown(this);
}

bool Town::canRecruit(ProtoType type)
{
	return tile_->unit() == nullptr && GameManager::get()->currentPlayer() == owner();
}
