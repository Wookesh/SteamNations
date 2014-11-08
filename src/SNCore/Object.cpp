#include "Object.hpp"
#include "Tile.hpp"

Object::Object(Tile *tile, QObject *parent) : QObject(parent), owner_(nullptr), tile_(tile)
{
	
}

Object::~Object()
{
	
}

void Object::setTile(Tile* tile)
{
	tile_ = tile;
}

Tile* Object::tile() const
{
	return tile_;
}

Player *Object::owner() const
{
	return owner_;
}

void Object::setOwner(Player *owner)
{
	owner_ = owner;
	emit ownerChanged();
}

