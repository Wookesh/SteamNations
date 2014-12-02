#include "Settler.hpp"
#include "Prototypes/SettlerPrototype.hpp"
#include "Town.hpp"
#include "../Tile.hpp"
#include "../GameManager.hpp"
#include "../Board.hpp"
#include "../Player.hpp"
#include <QDebug>

Settler::Settler(Tile *tile, const SettlerPrototype *prototype, Player *owner, QObject *parent) : Unit(tile, prototype, owner, parent)
{

}

Settler::~Settler()
{
	if (tile_ != nullptr)
		tile_->setUnit(nullptr);
	
	if (owner_ != nullptr)
		owner_->destroyUnit(this);
}

bool Settler::canSettle(Tile * tile) const
{
	if (tile == tile_ && tile->town() == nullptr && GameManager::get()->currentPlayer() == owner_)
		return true;
	return false;
}

bool Settler::settle()
{
	if (!canSettle(tile_))
		return false;
	
	Town *town = createTown();
	
	if (owner()->capital() == nullptr) {
		owner()->setCapital(town);
		emit capitalCreated(owner_);
	}
	emit townCreated(owner_);
	
	return true;
}


Town *Settler::createTown()
{
	Town * town = new Town(tile_, owner_);
	GameManager::get()->addObject(town);
	tile_->setTown(town);
	return town;
}

void Settler::getAttacked(Unit *) 
{
	
}

