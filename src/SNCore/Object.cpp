#include "Object.hpp"

Object::Object(QObject *parent) : QObject(parent)
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

