#include <limits>
#include <algorithm>
#include "Simple.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Player.hpp"

const SNTypes::heur minInf = std::numeric_limits<SNTypes::heur>::min();
const int checkingRange = 7;

SNTypes::heur Simple::unitHeuristic(Unit* unit, Tile* tile)
{
	if (tile->unit()) {
		Unit *unitFromTile = tile->unit();
		if (unitFromTile->owner() == unit->owner()) 
			return minInf;
		if (dynamic_cast<Soldier *>(unit)) {
			return Simple::soldierUnitValue(dynamic_cast<Soldier *>(unit), unitFromTile);
		}
		return minInf;
	}
	if (tile->town()){
		Town *townFromTile = tile->town();
		if (townFromTile->owner() == unit->owner()) 
			return minInf;
        if (dynamic_cast<Soldier *>(unit)) {
            return Simple::soldierTownValue(dynamic_cast<Soldier *>(unit), townFromTile);
		}
        if (dynamic_cast<Settler *>(unit)) {
            return Simple::settlerTownValue(dynamic_cast<Settler *>(unit), townFromTile);
		}
		return minInf; //nie powinno tu dojść
	}
	return Simple::unitWanderValue(unit, tile);
}

SNTypes::heur Simple::settlerTownValue(Settler *settler, Town *town)
{
	SNTypes::heur length = (GameManager::get()->board()->pathToTile(settler->tile(), town->tile())).length();
	//TODO food + typ
	return -length + 3;
}

SNTypes::heur Simple::soldierTownValue(Soldier *soldier, Town *town)
{
	SNTypes::heur length = (GameManager::get()->board()->pathToTile(soldier->tile(), town->tile())).length();
	//TODO nasze - ich
	return -length + 4;
}

SNTypes::heur Simple::soldierUnitValue(Soldier *soldier, Unit *unit)
{
	SNTypes::heur length = (GameManager::get()->board()->pathToTile(soldier->tile(), unit->tile())).length();
	//TODO reszta
	return -length + 3;
}

SNTypes::heur Simple::unitWanderValue(Unit *unit, Tile *tile)
{
	SNTypes::heur length = (GameManager::get()->board()->pathToTile(unit->tile(), tile)).length();
	//TODO food + typ
	return -length;
}

SNTypes::heur Simple::economyHeuristic(Player* player) 
{
	qint16 their = 0;
	QList <Player*> players = GameManager::get()->players();
	for (Player *other: players) {
		if (player != other)
			their += other->getUnitsCount();
	}
	their /= players.length();
	qint16 ours = player->getUnitsCount();
	return ours - their;
}

SNTypes::heur Simple::townBuildBuildingHeuristic(Town* town)
{
	QVector<Tile *> tiles = GameManager::get()->board()->getInRange(town->tile(), checkingRange);
	unsigned int minimum = checkingRange;
	for (Tile *tile: tiles) {
		minimum = std::min(minimum, GameManager::get()->board()->getAbsoluteDistance(town->tile(), tile));
	}
	return minimum;
}

SNTypes::heur Simple::townBuildUnitHeuristic(Town* town)
{
	QVector<Tile *> tiles = GameManager::get()->board()->getInRange(town->tile(), checkingRange);
	unsigned int minimum = checkingRange;
	for (Tile *tile: tiles) {
		minimum = std::min(minimum, GameManager::get()->board()->getAbsoluteDistance(town->tile(), tile));
	}
	return -((SNTypes::heur)minimum);
}



