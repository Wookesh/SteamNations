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
class Settler;

namespace AI {
	
	const SNTypes::heur minInf = std::numeric_limits<SNTypes::heur>::min();
	const int checkingRange = 7;
	const int sigmaCheckingRange = 3; //sigma = nasze - ich
	const int townCapturePriority = 5;
	const int unitAttackPriority = 4;
	const int wanderPriority = 0;
	
	QSet<Tile *> getAllTargets(Player *player);
	Tile *evaluate(Player *player, Unit *unit, SNTypes::heur (*heuristic)(Unit *,Tile *));
	
	SNTypes::heur soldierUnitValue(Soldier *soldier, Unit *unit);
	SNTypes::heur soldierTownValue(Soldier *soldier, Town *town);
	SNTypes::heur unitWanderValue(Unit *unit, Tile *tile);
	SNTypes::heur economyHeuristic(Player* player); //budowac jednostki czy budynki
	SNTypes::heur townBuildBuildingHeuristic(Town* town); //czy dobry town do budowania budynkow
	SNTypes::heur townBuildUnitHeuristic(Town* town); // czy dobry town do budowania jednostek
	SNTypes::heur soldierHeuristic(Unit *unit, Tile* tile); //ocena tile'a przez soldiera
	SNTypes::heur settlerHeuristic(Unit *unit, Tile* tile); //ocena tile'a przez settlera 
	SNTypes::heur settlerSettleHeuristic(Settler *settler, Tile *tile); //ocena tile do settlowania przez settlera
}

#endif