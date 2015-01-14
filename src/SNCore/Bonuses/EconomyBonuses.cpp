#include "EconomyBonuses.hpp"
#include <Player.hpp>
#include <Objects/Prototypes/SoldierPrototype.hpp>


/*
 * Tier1
 */

EconomyT1Bonus::EconomyT1Bonus() : Bonus (1, BonusType::Eco) {

}

bool EconomyT1Bonus::apply(Player *player) {
	// TODO
	
	return true;
}

/*
 * Tier2
 */

EconomyT2Bonus::EconomyT2Bonus() : Bonus (2, BonusType::Eco) {

}

bool EconomyT2Bonus::apply(Player *player) {
	// TODO
	
	return true;
}

/*
 * Tier3
 */

EconomyT3Bonus::EconomyT3Bonus() : Bonus (3, BonusType::Eco) {

}

bool EconomyT3Bonus::apply(Player *player) {
	// TODO
	
	return true;
}


