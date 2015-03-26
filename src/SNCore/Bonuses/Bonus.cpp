#include "Bonus.hpp"
#include <Player.hpp>
#include <QDebug>

Bonus::Bonus (SNTypes::tier tier, BonusType type) : tier_(tier), type_(type)
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
