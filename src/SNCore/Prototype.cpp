#include "Prototype.hpp"

Prototype::Prototype(const QString &name, int moveRange, int cost) : 
	name_(name), 
	moveRange_(moveRange), 
	cost_(cost)
{

}

Prototype::~Prototype()
{

}

int Prototype::cost() const
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

int Prototype::moveRange() const
{
	return moveRange_;
}

void Prototype::setMoveRange(int moveRange)
{
	moveRange_ = moveRange;
}
