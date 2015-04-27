#ifndef AI_MODULE_HPP
#define AI_MODULE_HPP

#include "SNCore/SNTypes.hpp"
#include "SNCore/Objects/Prototypes/Prototypes.hpp"
#include "SNCore/Bonuses/Bonuses.hpp"

#include <limits>
#include <QVector>
#include <QMap>

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
	const int townCapturePriority = 4;
	const int unitAttackPriority = 6;
	const int wanderPriority = 0;
	const int turnWithoutSettleMax = 4;
	const float forfeitTownRatio = 0.5;
	const float goodCounterRatio = 1;
	const float defensePathRatio = 0.5;
	const float warfarePathRatio = 1;
	const int maxTimeWithoutSettler = 6;
	
	Tile *evaluate(Player *player, Unit *unit, SNTypes::heur (*heuristic)(Unit *,Tile *));
	
	SNTypes::heur soldierHeuristic(Unit *unit, Tile* tile); //ocena tile'a przez soldiera
	SNTypes::heur soldierUnitValue(Soldier *soldier, Unit *unit);
	SNTypes::heur soldierTownValue(Soldier *soldier, Town *town);
	SNTypes::heur soldierWanderValue(Unit *unit, Tile *tile); //heura dla soldiera do kazdego tile'a, nietylko nieodkrytego
	
	SNTypes::heur settlerHeuristic(Unit *unit, Tile* tile); //ocena tile'a przez settlera 
	SNTypes::heur settlerSettleHeuristic(Settler *settler, Tile *tile); //ocena tile do settlowania przez settlera
	SNTypes::heur settlerSettleCapitalHeuristic(Settler *settler, Tile *tile); //ocena tile do settlowania przez settlera
	SNTypes::heur settlerWanderValue(Settler *settler, Tile *tile);
	
	SNTypes::heur townCreateSoldierHeuristic(Town *town); //w ktorym townie budowac soldiera
	SNTypes::heur townCreateSettlerHeuristic(Town *town); //w ktorym townie budowac settlera
	QList<PrototypeType> whichUnitsCreate(Player *player);
	QMap<Town *, PrototypeType> buildHeuristic(Player *player);
	
	BonusType whichTechnologyPath(Player *player);
}

#endif