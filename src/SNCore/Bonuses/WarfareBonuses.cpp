#include "WarfareBonuses.hpp"
#include <Player.hpp>

WarfareT1Bonus::WarfareT1Bonus (Player *player) : Bonus (player, 1, BonusType::War) {

}


bool WarfareT1Bonus::apply() {
	if (!canApply())
		return false;
}

