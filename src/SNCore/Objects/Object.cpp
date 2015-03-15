#include "Object.hpp"
#include "../Player.hpp"
#include "../Tile.hpp"
#include "../GameManager.hpp"

Object::Object(Tile *tile, ObjectType type, Player *owner, QObject *parent) :
	QObject(parent), owner_(owner), tile_(tile), type_(type), id_(Serial::EmptyUid)
{
}

Object::~Object()
{
	emit objectDestroyed(id_);
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
	emit ownerChanged(owner);
}
void Object::setType(ObjectType type)
{
	type_ = type;
}

ObjectType Object::type() const
{
	return type_;
}

UID Object::id() const
{
	return id_;
}

void Object::setId(const UID id)
{
	if (id_ == Serial::EmptyUid)
		id_ = id;
}

QDataStream &operator<<(QDataStream &out, const Object &object)
{
	out << object.owner()->name() << object.type();
	return out;
}

QDataStream &operator>>(QDataStream &in, Object &object)
{
// 	QString playerName;
// 	in >> playerName >> object.type_;
	return in;
}
