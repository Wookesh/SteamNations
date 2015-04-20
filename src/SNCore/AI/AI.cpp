#include "AI.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/Objects/Town.hpp"
#include "SNCore/Objects/Unit.hpp"
#include "SNCore/Objects/Settler.hpp"
#include "SNCore/Objects/Soldier.hpp"

#include <QVector>
#include <QQueue>

namespace AI {
	
	QSet<Tile *> getAllTargets(Player *player) 
	{
		static Player *previousPlayer = nullptr;
		static QSet<Tile *> previousTargets;
		if (previousPlayer == player)
			return previousTargets;
		
		QSet<Tile *> visitedTiles;
		QSet<Tile *> targetTiles;
		QQueue<Tile *> tilesToVisit;
		
		tilesToVisit.enqueue(player->capital()->tile());
		
		while (!tilesToVisit.isEmpty()) {
			Tile *tile = tilesToVisit.dequeue();
			visitedTiles.insert(tile);
			if (!tile->visible(player)) {
				targetTiles.insert(tile);
			} else {
				if ((tile->unit() != nullptr && tile->unit()->owner() != player) 
					|| (tile->town() != nullptr && tile->town()->owner() != player))
					targetTiles.insert(tile);
				
				QVector<Tile *> neighbours = GameManager::get()->board()->getNeighbours(tile);
				for (Tile *nTile : neighbours) {
					if (!visitedTiles.contains(nTile))
						tilesToVisit.enqueue(nTile);
				}
			}
		}
		
		previousPlayer = player;
		previousTargets = targetTiles;
		
		return targetTiles;
	}
	
	Tile *evaluate(Player *player, Unit *unit, SNTypes::heur (*heuristic)(Unit *,Tile *))
	{
		QSet<Tile *> targets = getAllTargets(player);
		QPair<int, Tile *> bestTarget;
		for (Tile *tile: targets) {
			int hVal = heuristic(unit, tile);
			bestTarget = hVal > bestTarget.first ? qMakePair(hVal, tile) : bestTarget;
		}
		return bestTarget.second;
	}
	
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
		for (Tile *tile: tiles) 
			minimum = std::min(minimum, GameManager::get()->board()->getAbsoluteDistance(town->tile(), tile));
		return minimum;
	}

	SNTypes::heur townBuildUnitHeuristic(Town* town)
	{
		QVector<Tile *> tiles = GameManager::get()->board()->getInRange(town->tile(), checkingRange);
		unsigned int minimum = checkingRange;
		for (Tile *tile: tiles) 
			minimum = std::min(minimum, GameManager::get()->board()->getAbsoluteDistance(town->tile(), tile));
		return -((SNTypes::heur)minimum);
	}

	SNTypes::heur soldierHeuristic(Unit* unit, Tile* tile)
	{
		Soldier *soldier = static_cast<Soldier *>(unit);
		if (tile->unit()) {
			Unit *unitFromTile = tile->unit();
			if (unitFromTile->owner() == soldier->owner()) 
				return minInf;
			return soldierUnitValue(soldier, unitFromTile);
		}
		if (tile->town()) {
			Town *townFromTile = tile->town();
			if (townFromTile->owner() == soldier->owner()) 
				return minInf;
			return soldierTownValue(soldier, townFromTile);
		}
		return unitWanderValue(soldier, tile);
	}
	
	SNTypes::heur settlerHeuristic(Unit *unit, Tile* tile)
	{
		Settler *settler = static_cast<Settler *>(unit);
		if (tile->unit() || tile->town()) 
			return minInf;
		if (tile->visible(settler->owner()))
			return settlerSettleHeuristic(settler, tile);
		return unitWanderValue(settler, tile);
	}
	
	SNTypes::heur settlerSettleHeuristic(Settler *settler, Tile *tile) 
	{
		QVector<Tile *> tiles = GameManager::get()->board()->getInRange(tile, 1);
		int resources[4] = {0, 0, 0, 0};
		for (Tile *newTownTiles: tiles) {
			if (newTownTiles->resource() == Resource::Gold) ++resources[0];
			if (newTownTiles->resource() == Resource::Research) ++resources[1];
			if (newTownTiles->resource() == Resource::Food) ++resources[2];
			if (newTownTiles->resource() == Resource::None) ++resources[3];
		}
		//najlepszy town to taki ktory ma 4 golda i 3 food/research.
		//najgorszy to jak ma 7 none
		return (resources[0] + 1)*(std::abs(resources[1] - resources[2]) + 1) - (resources[3]);
	}
	
	SNTypes::heur getSigma(Tile *ours, Tile *their) {
		QVector<Tile *> aroundTheir = GameManager::get()->board()->getInRange(their, sigmaCheckingRange);
		QVector<Tile *> aroundOurs = GameManager::get()->board()->getInRange(ours, sigmaCheckingRange);
		
		int myPower = 0;
		int theirPower = 0;
		
		for (Tile *tile: aroundTheir) {
			if (tile->unit()) {
				if (tile->unit()->pType() != PrototypeType::Settler){
					if (tile->unit()->owner() == ours->unit()->owner())
						myPower++;
					if (tile->unit()->owner() == their->unit()->owner())
						theirPower++;
				}
			}
		}
		
		for (Tile *tile: aroundOurs) {
			if (tile->unit()) {
				if (tile->unit()->pType() != PrototypeType::Settler){
					if (tile->unit()->owner() == ours->unit()->owner())
						myPower++;
					if (tile->unit()->owner() == their->unit()->owner())
						theirPower++;
				}
			}
		}
		return myPower - theirPower;
	}

	SNTypes::heur soldierTownValue(Soldier *soldier, Town *town)
	{
		SNTypes::heur length = (GameManager::get()->board()->pathToTile(soldier->tile(), town->tile())).length();
		int sigma = getSigma(soldier->tile(), town->tile());
		return -length + sigma + townCapturePriority;
	}

	SNTypes::heur soldierUnitValue(Soldier *soldier, Unit *unit)
	{
		SNTypes::heur length = (GameManager::get()->board()->pathToTile(soldier->tile(), unit->tile())).length();
		int sigma = getSigma(soldier->tile(), unit->tile());
		return -length + sigma + unitAttackPriority;
	}

	SNTypes::heur unitWanderValue(Unit *unit, Tile *tile)
	{
		SNTypes::heur length = (GameManager::get()->board()->pathToTile(unit->tile(), tile)).length();
		
		return -length + unit->visionRange();
	}
}