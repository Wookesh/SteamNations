#include "Prototype.hpp"

Prototype::Prototype(ProtoType type, const QString &name, int moveRange, int cost) :
	type_(type),
	name_(name), 
	moveRange_(moveRange), 
	cost_(cost)
{

}

Prototype::~Prototype()
{

}

ProtoType Prototype::type() const
{
	return type_;
}


unsigned int Prototype::cost() const
{
	return cost_;
}

void Prototype::setCost(int cost)
{
	cost_ = cost;
}

QString Prototype::name() const
{
	return name_;
}

void Prototype::setName(const QString &name)
{
	name_ = name;
}

quint8 Prototype::moveRange() const
{
	return moveRange_;
}

void Prototype::setMoveRange(quint8 moveRange)
{
	moveRange_ = moveRange;
}
