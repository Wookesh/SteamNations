#include "Object.hpp"
#include "Tile.hpp"

Object::Object(Tile *tile, SN::ObjectType type, QObject *parent) : QObject(parent), owner_(nullptr), tile_(tile), type_(type)
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
void Object::setType(SN::ObjectType type)
{
	type_ = type;
}

SN::ObjectType Object::type()
{
	return type_;
}

