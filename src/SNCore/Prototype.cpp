#include "Prototype.hpp"

Prototype::Prototype(const QString &name, int moveRange, int cost) : name_(name), 
	moveRange_(moveRange), cost_(cost)
{

}

Prototype::~Prototype()
{

}

int Prototype::cost() const
{

}

void Prototype::setCost(int cost)
{

}

QString Prototype::name() const
{

}

void Prototype::setName(const QString &name)
{

}

int Prototype::moveRange() const
{

}

void Prototype::setMoveRange(int moveRange)
{

}

Unit *Prototype::createUnit()
{

}
