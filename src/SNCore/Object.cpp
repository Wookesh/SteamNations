#include "Object.hpp"
#include "Tile.hpp"
#include "GameManager.hpp"

Object::Object(Tile *tile, Type type, QObject *parent) : QObject(parent), owner_(nullptr), tile_(tile), type_(type), id_(GameManager::get()->serial()->next())
{
	GameManager::get()->addObject(id(), this);
}

Object::~Object()
{
	
}

void Object::setTile(Tile *tile)
{
	tile_ = tile;
}

Tile *Object::tile()
{
	return tile_;
}

const Tile *Object::tile() const
{
	return tile_;
}

Player *Object::owner()
{
	return owner_;
}

const Player *Object::owner() const
{
	return owner_;
}

void Object::setOwner(Player *owner)
{
	owner_ = owner;
	emit ownerChanged();
}
void Object::setType(Type type)
{
	type_ = type;
}

Object::Type Object::type() const
{
	return type_;
}

UID Object::id() const
{
	return id_;
}

