#include "Town.hpp"
#include "Unit.hpp"
#include "../Tile.hpp"
#include "../Player.hpp"
#include "../GameManager.hpp"
#include <Board.hpp>
#include <QDebug>

Town::Town(Tile *tile, Player *owner, const QString &name, QObject *parent) :
	Object(tile, ObjectType::Town, owner, parent), name_(name)
{
	owner->obtainTown(this);
	for (Tile *nTile : GameManager::get()->board()->getInRange(tile_, 1))
		if (nTile->localTown() == nullptr) {
			nTile->setLocalTown(this);
			townTiles_.push_back(nTile);
		}
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
	qDebug() << name() << __FUNCTION__;
	for (Tile *tile : townTiles_)
		if (tile->resource() != Resource::None)
			owner_->addResource(tile->resource(), tile->takeResources());
}


QString Town::name() const
{
	return name_;
}

void Town::updateAfter()
{
	
}

Unit *Town::createUnit(PrototypeType type)
{
	if (!canRecruit(type))
		return nullptr;
	
	owner_->removeResource(Resource::Gold, owner_->prototype(type)->cost());
	Unit *newUnit = owner_->createUnit(type, tile_);
	return newUnit;
}

void Town::getCaptured(Player *player)
{
	setOwner(player);
	player->obtainTown(this);
}

bool Town::canRecruit(PrototypeType type)
{
	if (tile_->unit() == nullptr &&
		GameManager::get()->currentPlayer() == owner() &&
		owner()->resource(Resource::Gold) >= owner()->prototype(type)->cost())
		return true;
	return false;
}
