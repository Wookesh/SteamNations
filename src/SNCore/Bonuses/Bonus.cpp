#include "Bonus.hpp"
#include <Player.hpp>

Bonus::Bonus (Player *player, SNTypes::tier tier, BonusType type) : tier_(tier), type_(type), player_(player)
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

Player *Bonus::player() const 
{
	return player_;
}

bool Bonus::canApply() const 
{
	return (player_->hasBonus(type_, tier_ - 1) &&
		!player_->hasBonus(type_, tier_) &&
		player_->resource(Resource::Research) >= cost());
	
}
