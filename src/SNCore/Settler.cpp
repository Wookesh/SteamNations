#include "Settler.hpp"
#include "SettlerPrototype.hpp"
#include "Town.hpp"
#include "Tile.hpp"
#include "GameManager.hpp"
#include <QDebug>

Settler::Settler(Tile *tile, const SettlerPrototype *prototype, Player *owner, QObject *parent) : Unit(tile, prototype, owner, parent)
{

}

Settler::~Settler()
{

}

bool Settler::canSettle(Tile * tile) const
{
	if (tile == tile_ && tile->town() == nullptr && GameManager::get()->currentPlayer() == owner_)
		return true;
	return false;
}

bool Settler::settle()
{
	createTown();
	return true;
	
}


Town *Settler::createTown()
{
	Town * town = new Town(tile_, owner_);
	tile_->setTown(town);
	tile_->setUnit(nullptr);
	delete this;
	return town;
}

void Settler::getAttacked (Unit *) {
	
}

