#include "EconomyBonuses.hpp"
#include <Player.hpp>
#include <Objects/Prototypes/SoldierPrototype.hpp>


/*
 * Tier1
 */

EconomyT1Bonus::EconomyT1Bonus() : Bonus (1, BonusType::Eco, SNCfg::ECO_TECH_DESCRIPTION_TIER1) {

}

bool EconomyT1Bonus::apply(Player *player) {
	if (!canApply(player))
		return false;
	
	player->setBonusIncome(player->bonusIncome() + 0.1);
	
	return true;
}

/*
 * Tier2
 */

EconomyT2Bonus::EconomyT2Bonus() : Bonus (2, BonusType::Eco, SNCfg::ECO_TECH_DESCRIPTION_TIER2) {

}

bool EconomyT2Bonus::apply(Player *player) {
	if (!canApply(player))
		return false;
	
	Prototype *prototype = player->prototype(PrototypeType::Settler);
	prototype->setActionPoints(prototype->actionPoints() + 1);
	
	return true;
}

/*
 * Tier3
 */

EconomyT3Bonus::EconomyT3Bonus() : Bonus (3, BonusType::Eco, SNCfg::ECO_TECH_DESCRIPTION_TIER3) {

}

bool EconomyT3Bonus::apply(Player *player) {
	if (!canApply(player))
		return false;
	
	player->setBonusGold(player->bonusGold() + 1.);
	
	return true;
}


