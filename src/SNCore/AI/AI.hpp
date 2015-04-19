#ifndef AI_MODULE_HPP
#define AI_MODULE_HPP

#include <limits>
#include <QSet>
#include "SNCore/SNTypes.hpp"

class Tile;
class Player;
class Unit;
class Soldier;
class Town;

namespace AI {
	
	const SNTypes::heur minInf = std::numeric_limits<SNTypes::heur>::min();
	const int checkingRange = 7;
	const int sigmaCheckingRange = 3; //sigma = nasze - ich
	const int townCapturePriority = 5;
	const int unitAttackPriority = 4;
	const int wanderPriority = 0;
	
	QSet<Tile *> getAllTargets(Player *player);
	Tile *evaluate(Player *player, Unit *unit, int (*heuristic)(Unit *,Tile *));
	
	SNTypes::heur soldierUnitValue(Soldier *soldier, Unit *unit);
	SNTypes::heur soldierTownValue(Soldier *soldier, Town *town);
	SNTypes::heur unitWanderValue(Unit *unit, Tile *tile);
}

#endif