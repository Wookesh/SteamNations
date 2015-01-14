#include "DefenseBonuses.hpp"
#include <Player.hpp>
#include <Objects/Prototypes/SoldierPrototype.hpp>


/*
 * Tier1
 */

DefenseT1Bonus::DefenseT1Bonus() : Bonus (1, BonusType::Def) {

}

bool DefenseT1Bonus::apply(Player *player) {
	if (!canApply(player))
		return false;
	
	for (Prototype *element : player->prototypes()) {
		element->addHealthBonus(0.1f);
	}
	
	return true;
}

/*
 * Tier2
 */

DefenseT2Bonus::DefenseT2Bonus() : Bonus (2, BonusType::Def) {

}

bool DefenseT2Bonus::apply(Player *player) {
	if (!canApply(player))
		return false;
	
	for (Prototype *element : player->soldierPrototypes()) {
		SoldierPrototype *prototype = dynamic_cast<SoldierPrototype *>(element);
		prototype->setCtrAtkRange(prototype->ctrAtkRange() + 1);
	}
	
	return true;
}

/*
 * Tier3
 */

DefenseT3Bonus::DefenseT3Bonus() : Bonus (3, BonusType::Def) {

}

bool DefenseT3Bonus::apply(Player *player) {
	// TODO
	
	return true;
}


