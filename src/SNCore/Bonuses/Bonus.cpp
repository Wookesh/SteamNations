#include "Bonus.hpp"
#include <Player.hpp>
#include <QDebug>

Bonus::Bonus (SNTypes::tier tier, BonusType type, QString description) : tier_(tier), type_(type), description_(description)
{

}

Bonus::~Bonus() 
{

}

SNTypes::amount Bonus::cost() const {
	return bonusCost[tier_];
}


SNTypes::tier Bonus::tier() const 
{
	return tier_;
}

BonusType Bonus::type() const 
{
	return type_;
}

bool Bonus::canApply(Player *player) const 
{
	
	return ((tier_ == 1 || player->hasBonus(type_, tier_ - 1)) &&
		!player->hasBonus(type_, tier_) &&
		player->resource(Resource::Research) >= cost());
	
}

QString Bonus::description() const
{
	return description_;
}
