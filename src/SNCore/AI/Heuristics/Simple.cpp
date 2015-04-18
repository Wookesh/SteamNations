#include <limits>
#include <algorithm>
#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Player.hpp"

#include "SNCore/SNTypes.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/Objects/Objects.hpp"

const SNTypes::heur minInf = std::numeric_limits<SNTypes::heur>::min();
const int checkingRange = 7;

SNTypes::heur settlerTownValue(Settler *settler, Town *town)
{
	SNTypes::heur length = (GameManager::get()->board()->pathToTile(settler->tile(), town->tile())).length();
	//TODO food + typ
	return -length + 3;
}

SNTypes::heur soldierTownValue(Soldier *soldier, Town *town)
{
	SNTypes::heur length = (GameManager::get()->board()->pathToTile(soldier->tile(), town->tile())).length();
	//TODO nasze - ich
	return -length + 4;
}

SNTypes::heur soldierUnitValue(Soldier *soldier, Unit *unit)
{
	SNTypes::heur length = (GameManager::get()->board()->pathToTile(soldier->tile(), unit->tile())).length();
	//TODO reszta
	return -length + 3;
}

SNTypes::heur unitWanderValue(Unit *unit, Tile *tile)
{
	SNTypes::heur length = (GameManager::get()->board()->pathToTile(unit->tile(), tile)).length();
	//TODO food + typ
	return -length;
}

namespace SimpleHeuristic {
	
	SNTypes::heur economyHeuristic(Player* player) 
	{
		qint16 their = 0;
		QList <Player*> players = GameManager::get()->players();
		for (Player *other: players) {
			if (player != other)
				their += other->getUnitsCount();
		}
		their /= players.length() - 1;
		qint16 ours = player->getUnitsCount();
		return ours - their;
	}

	SNTypes::heur townBuildBuildingHeuristic(Town* town)
	{
		QVector<Tile *> tiles = GameManager::get()->board()->getInRange(town->tile(), checkingRange);
		unsigned int minimum = checkingRange;
		for (Tile *tile: tiles) {
			minimum = std::min(minimum, GameManager::get()->board()->getAbsoluteDistance(town->tile(), tile));
		}
		return minimum;
	}

	SNTypes::heur townBuildUnitHeuristic(Town* town)
	{
		QVector<Tile *> tiles = GameManager::get()->board()->getInRange(town->tile(), checkingRange);
		unsigned int minimum = checkingRange;
		for (Tile *tile: tiles) {
			minimum = std::min(minimum, GameManager::get()->board()->getAbsoluteDistance(town->tile(), tile));
		}
		return -((SNTypes::heur)minimum);
	}

	SNTypes::heur soldierHeuristic(Soldier* soldier, Tile* tile)
	{
		if (tile->unit()) {
			Unit *unitFromTile = tile->unit();
			if (unitFromTile->owner() == soldier->owner()) 
				return minInf;
			return soldierUnitValue(soldier, unitFromTile);
		}
		if (tile->town()){
			Town *townFromTile = tile->town();
			if (townFromTile->owner() == soldier->owner()) 
				return minInf;
			return soldierTownValue(soldier, townFromTile);
		}
		return unitWanderValue(soldier, tile);
	}
	
	SNTypes::heur settlerHeuristic(Settler* settler, Tile* tile)
	{
		if (tile->unit()) 
			return minInf;

		if (tile->town()){
			Town *townFromTile = tile->town();
			if (townFromTile->owner() == settler->owner()) 
				return minInf;
			return settlerTownValue(settler, townFromTile);
		}
		return unitWanderValue(settler, tile);
	}

	

}
