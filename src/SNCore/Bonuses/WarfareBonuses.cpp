#include "WarfareBonuses.hpp"
#include <Player.hpp>
#include <Objects/Prototypes/SoldierPrototype.hpp>


/*
 * Tier1
 */

WarfareT1Bonus::WarfareT1Bonus() : Bonus (1, BonusType::War, SNCfg::WAR_TECH_DESCRIPTION_TIER1) {

}

bool WarfareT1Bonus::apply(Player *player) {
	if (!canApply(player))
		return false;
	
	for (Prototype *element : player->soldierPrototypes()) {
		SoldierPrototype *prototype = dynamic_cast<SoldierPrototype *>(element);
		prototype->addMultiplier(0.1f);
	}
	
	return true;
}

/*
 * Tier2
 */

WarfareT2Bonus::WarfareT2Bonus() : Bonus (2, BonusType::War, SNCfg::WAR_TECH_DESCRIPTION_TIER2) {

}

bool WarfareT2Bonus::apply(Player *player) {
	if (!canApply(player))
		return false;
	
	for (Prototype *element : player->soldierPrototypes()) {
		SoldierPrototype *prototype = dynamic_cast<SoldierPrototype *>(element);
		prototype->setAttackRange(prototype->attackRange() + 1);
	}
	
	return true;
}

/*
 * Tier3
 */

WarfareT3Bonus::WarfareT3Bonus() : Bonus (3, BonusType::War, SNCfg::WAR_TECH_DESCRIPTION_TIER3) {

}

bool WarfareT3Bonus::apply(Player *player) {
	if (!canApply(player))
		return false;
	
	for (Prototype *prototype : player->soldierPrototypes()) {
		prototype->setActionPoints(prototype->actionPoints() + 1);
	}

	
	return true;
}

