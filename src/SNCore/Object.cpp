#include "Object.hpp"

Object::Object(QObject *parent) : QObject(parent)
{
	
}

Object::~Object()
{

}
void Object::setTile(Tile* tile)
{

}

Tile* Object::tile() const
{
	
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

