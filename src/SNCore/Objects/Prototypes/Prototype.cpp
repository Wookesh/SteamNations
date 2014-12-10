#include "Prototype.hpp"

Prototype::Prototype(PrototypeType type, 
	const QString &name, SNTypes::ap actionPoints, SNTypes::amount cost, SNTypes::hp health) :
	type_(type), name_(name), actionPoints_(actionPoints), cost_(cost), health_(health)
{

}

Prototype::~Prototype()
{

}

PrototypeType Prototype::type() const
{
	return type_;
}


SNTypes::amount Prototype::cost() const
{
	return cost_;
}

void Prototype::setCost(SNTypes::amount cost)
{
	cost_ = cost;
}

const QString &Prototype::name() const
{
	return name_;
}

void Prototype::setName(const QString &name)
{
	name_ = name;
}

SNTypes::ap Prototype::actionPoints() const
{
	return actionPoints_;
}

void Prototype::setActionPoints(SNTypes::ap actionPoints)
{
	actionPoints_ = actionPoints;
}

SNTypes::hp Prototype::health() const
{
	return health_;
}

void Prototype::setHealth(SNTypes::hp health)
{
	health_ = health;
}
