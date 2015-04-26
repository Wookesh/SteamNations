#include "AI.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/Objects/Town.hpp"
#include "SNCore/Objects/Unit.hpp"
#include "SNCore/Objects/Settler.hpp"
#include "SNCore/Objects/Soldier.hpp"

#include <QQueue>
#include <QSet>
#include <QPoint>
#include <QList>
#include <QMap>

namespace AI {
	
	Tile *evaluate(Player *player, Unit *unit, SNTypes::heur (*heuristic)(Unit *,Tile *))
	{
		QPair<int, Tile *> bestTarget(minInf, nullptr);
		
		QSet<Tile *> visitedTiles;
		QQueue<Tile *> tilesToVisit;
		
		tilesToVisit.enqueue(unit->tile());
		visitedTiles.insert(unit->tile());
		
		while (!tilesToVisit.isEmpty()) {
			Tile *tile = tilesToVisit.dequeue();
			if (tile->visible(player)) {
				QVector<Tile *> neighbours = GameManager::get()->board()->getNeighbours(tile);
				for (Tile *nTile : neighbours) {
					if (!visitedTiles.contains(nTile)) {
						tilesToVisit.enqueue(nTile);
						visitedTiles.insert(nTile);
					}
				}
			}
			int hVal = heuristic(unit, tile);
			bestTarget = hVal > bestTarget.first ? qMakePair(hVal, tile) : bestTarget;
		}
		
		return bestTarget.second;
	}
	
	SNTypes::heur getSigma(Tile *ours, Tile *their, Player *me, Player *enemy) 
	{
		QVector<Tile *> aroundTheir = GameManager::get()->board()->getInRange(their, sigmaCheckingRange);
		QVector<Tile *> aroundOurs = GameManager::get()->board()->getInRange(ours, sigmaCheckingRange);
		
		int myPower = 0;
		int theirPower = 0;
		
		for (Tile *tile: aroundTheir) {
			if (tile->unit()) {
				if (tile->unit()->pType() != PrototypeType::Settler) {
					if (tile->unit()->owner() == me)
						myPower++;
					if (tile->unit()->owner() == enemy)
						theirPower++;
				}
			}
		}
		
		for (Tile *tile: aroundOurs) {
			if (tile->unit()) {
				if (tile->unit()->pType() != PrototypeType::Settler) {
					if (tile->unit()->owner() == me)
						myPower++;
					if (tile->unit()->owner() == enemy)
						theirPower++;
				}
			}
		}
		return myPower - theirPower;
	}
	
	SNTypes::heur getPowerAround(Tile *ours, Player *me, int range) 
	{
		QVector<Tile *> aroundOurs = GameManager::get()->board()->getInRange(ours, range);
		int myPower = 0;
		int theirPower = 0;
		
		for (Tile *tile: aroundOurs) {
			if (tile->unit()) {
				if (tile->unit()->pType() != PrototypeType::Settler) {
					if (tile->unit()->owner() == me)
						myPower++;
					else
						theirPower++;
				}
			} else if (tile->town()) {
				if (tile->town()->owner() == me) 
					myPower ++;
				else 
					theirPower++;
			}
		}
		
		return myPower - theirPower;
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
		if (!tile->visible(unit->owner()))
			return soldierWanderValue(soldier, tile);
		return minInf;
	}

	SNTypes::heur soldierTownValue(Soldier *soldier, Town *town)
	{
		SNTypes::heur length = (GameManager::get()->board()->pathToTile(soldier->tile(), town->tile())).length();
		int sigma = getSigma(soldier->tile(), town->tile(), soldier->owner(), town->owner());
		return -length + sigma + townCapturePriority;
	}

	SNTypes::heur soldierUnitValue(Soldier *soldier, Unit *unit)
	{
		SNTypes::heur length = (GameManager::get()->board()->pathToTile(soldier->tile(), unit->tile())).length();
		int sigma = getSigma(soldier->tile(), unit->tile(), soldier->owner(), unit->owner());
		return -length + sigma + unitAttackPriority;
	}

	SNTypes::heur soldierWanderValue(Unit *unit, Tile *tile)
	{
		ComputerPlayer *player = static_cast<ComputerPlayer *>(unit->owner());
		
		int playerNo = qrand() % GameManager::get()->players().length();
		if (player->playerToAttack() == nullptr) {
			player->setPlayerToAttack(GameManager::get()->players().at(playerNo) != unit->owner() ?
				GameManager::get()->players().at(playerNo) :
				GameManager::get()->players().at((playerNo + 1) % GameManager::get()->players().length()));
		}
		
		while ((player->playerToAttack()->getUnitsCount() == 0) && (player->playerToAttack()->getTownCount() == 0)) {
			player->setPlayerToAttack(GameManager::get()->players().at(playerNo) != unit->owner() ?
				GameManager::get()->players().at(playerNo) :
				GameManager::get()->players().at((playerNo + 1) % GameManager::get()->players().length()));
			playerNo = (playerNo + 1) % GameManager::get()->players().length();
		}
		
		SNTypes::heur direction = player->playerToAttack()->capital() ? GameManager::get()->board()->getAbsoluteDistance(unit->tile(), player->playerToAttack()->capital()->tile()) - 
			GameManager::get()->board()->getAbsoluteDistance(tile, player->playerToAttack()->capital()->tile()) + (qrand() % 4) - 3: 
			(qrand() % 4) - 3;
		
		SNTypes::heur length = (GameManager::get()->board()->pathToTile(unit->tile(), tile)).length();
		
		return -length + unit->visionRange() + direction/2;
	}
	
	SNTypes::heur settlerHeuristic(Unit *unit, Tile* tile)
	{
		Settler *settler = static_cast<Settler *>(unit);
		if (tile->unit() || tile->town()) 
			return minInf;
		
		if (tile->visible(settler->owner()))
			return settlerSettleHeuristic(settler, tile);
		
		return settlerWanderValue(settler, tile);
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
		//najlepszy town to taki ktory ma 3-4 fooda i 3-4 gold/research.
		//najgorszy to jak ma 7 none
		//FIXME 3~4 fooda, i inny surowiec, minimalizujemy None
		return (resources[2] + 1)*(std::abs(resources[1] - resources[0]) + 1) - (resources[3]);
	}
	
	SNTypes::heur settlerWanderValue(Settler* settler, Tile* tile)
	{
		
		if (settler->owner()->capital() == nullptr) {
			SNTypes::heur length = (GameManager::get()->board()->pathToTile(settler->tile(), tile)).length();
			if (settler->actionPoints() * (turnWithoutSettleMax - settler->turnWithoutSettle()) < length) {
				return minInf;
			}
		}
		SNTypes::heur tileValue = settlerSettleHeuristic(settler, tile);
		
		SNTypes::heur power = getPowerAround(tile, settler->owner(), sigmaCheckingRange);
		return tileValue * power;
	}


	SNTypes::heur townBuildUnitHeuristic(Town* town)
	{
		QVector<Tile *> tiles = GameManager::get()->board()->getInRange(town->tile(), checkingRange);
		unsigned int minimum = checkingRange;
		for (Tile *tile: tiles) 
			minimum = std::min(minimum, GameManager::get()->board()->getAbsoluteDistance(town->tile(), tile));
		return -((SNTypes::heur)minimum);
	}
	
	SNTypes::heur townCreateSoldierHeuristic(Town* town)
	{
		QVector<Tile *> aroundOurs = GameManager::get()->board()->getInRange(town->tile(), sigmaCheckingRange - 1);
		int myPower = 0;
		int theirPower = 0;
		
		for (Tile *tile: aroundOurs) {
			if (tile->unit()) {
				if (tile->unit()->pType() != PrototypeType::Settler) {
					if (tile->unit()->owner() == town->owner())
						myPower++;
					else
						theirPower++;
				}
			} else if (tile->town()) {
				if (tile->town()->owner() == town->owner()) 
					myPower++;
				else 
					theirPower++;
			}
		}
		qreal ratio = (myPower + 1) / (theirPower + 1);
		return ratio < forfeitTownRatio ? minInf : - myPower + theirPower;
	}
	
	SNTypes::heur townCreateSettlerHeuristic(Town* town)
	{
		return getPowerAround(town->tile(), town->owner(), sigmaCheckingRange - 1);
	}
	
	
	QList<PrototypeType> whichUnitsCreate(Player* player)
	{
		QList<PrototypeType> result;
		if (!player->towns().isEmpty()) {
			int gold = player->resource(Resource::Gold);
			ComputerPlayer *cp = static_cast<ComputerPlayer *>(player);
			if (GameManager::get()->currentTurn() - cp->lastTimeSettlerBought() > maxTimeWithoutSettler) {
				if (gold - SettlerPrototype::BASE_COST >= 0) {
					result.push_back(PrototypeType::Settler);
					gold -= SettlerPrototype::BASE_COST;
				} else {
					return result;
				}
			}
			QMap<Player *, int> infantries;
			QMap<Player *, int> heavies;
			QMap<Player *, int> artilleries;
			
			QList<Player *> players = GameManager::get()->players();
			for (Player *other: players) {
				infantries[other] = 0;
				heavies[other] = 0;
				artilleries[other] = 0;
			}
			
			for (Player *p: players)  {
				QVector<Unit *> units = p->units();
				for (Unit *unit: units) {
					if (unit->pType() == PrototypeType::Infantry)
						++infantries[p];
					if (unit->pType() == PrototypeType::Heavy)
						++heavies[p];
					if (unit->pType() == PrototypeType::Artillery)
						++artilleries[p];
				}
			}
			
			int infantry = 0;
			int heavy = 0;
			int artillery = 0;
			for(Player *p: players) {
				if (p != player) {
					infantry = std::max(infantry, infantries[p]);
					heavy = std::max(infantry, heavies[p]);
					artillery = std::max(infantry, artilleries[p]);
				}
			}
			
			qreal myArtilleryCounterPower = (infantries[player] + 1)/(artillery + 1);
			qreal myInfantryCounterPower = (heavies[player] + 1)/(infantry + 1);
			qreal myHeavyCounterPower = (artilleries[player] + 1)/(heavy + 1);
			bool biggerArmy = myInfantryCounterPower > goodCounterRatio && 
				myHeavyCounterPower > goodCounterRatio && 
				myArtilleryCounterPower > goodCounterRatio;
			bool noMoneyLeft = false;
			while ((result.length() < player->getTownCount()) && (!biggerArmy) && (!noMoneyLeft)) {
				
				if (infantry > heavy) {
					if (infantry > artillery) {
						if (heavy > artillery) { //i h a
							if (myInfantryCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Heavy] >= 0) {
									result.push_back(PrototypeType::Heavy);
									++heavies[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Heavy];
								} else {
									noMoneyLeft = true;
								}
							} else if (myHeavyCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Artillery] >= 0) {
									result.push_back(PrototypeType::Artillery);
									++artilleries[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Artillery];
								} else {
									noMoneyLeft = true;
								}
							} else if (myArtilleryCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Infantry] >= 0) {
									result.push_back(PrototypeType::Infantry);
									++infantries[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Infantry];
								} else {
									noMoneyLeft = true;
								}
							}
							
						} else { //i a h
							if (myInfantryCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Heavy] >= 0) {
									result.push_back(PrototypeType::Heavy);
									++heavies[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Heavy];
								} else {
									noMoneyLeft = true;
								}
							} else if (myArtilleryCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Infantry] >= 0) {
									result.push_back(PrototypeType::Infantry);
									++infantries[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Infantry];
								} else {
									noMoneyLeft = true;
								}
							} else if (myHeavyCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Artillery] >= 0) {
									result.push_back(PrototypeType::Artillery);
									++artilleries[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Artillery];
								} else {
									noMoneyLeft = true;
								}
							}
							
						}
					} else { // a i h
						if (myArtilleryCounterPower <= goodCounterRatio) {
							if (gold - SoldierPrototype::BASE_COST[PrototypeType::Infantry] >= 0) {
								result.push_back(PrototypeType::Infantry);
								++infantries[player];
								gold -= SoldierPrototype::BASE_COST[PrototypeType::Infantry];
							} else {
								noMoneyLeft = true;
							}
						
						} else if (myInfantryCounterPower <= goodCounterRatio) {
							if (gold - SoldierPrototype::BASE_COST[PrototypeType::Heavy] >= 0) {
								result.push_back(PrototypeType::Heavy);
								++heavies[player];
								gold -= SoldierPrototype::BASE_COST[PrototypeType::Heavy];
							} else {
								noMoneyLeft = true;
							}
						} else if (myHeavyCounterPower <= goodCounterRatio) {
							if (gold - SoldierPrototype::BASE_COST[PrototypeType::Artillery] >= 0) {
								result.push_back(PrototypeType::Artillery);
								++artilleries[player];
								gold -= SoldierPrototype::BASE_COST[PrototypeType::Artillery];
							} else {
								noMoneyLeft = true;
							}
						}
					}
				} else {
					if (infantry > artillery) { //h i a
						if (myHeavyCounterPower <= goodCounterRatio) {
							if (gold - SoldierPrototype::BASE_COST[PrototypeType::Artillery] >= 0) {
								result.push_back(PrototypeType::Artillery);
								++artilleries[player];
								gold -= SoldierPrototype::BASE_COST[PrototypeType::Artillery];
							} else {
								noMoneyLeft = true;
							}
						} else if (myInfantryCounterPower <= goodCounterRatio) {
							if (gold - SoldierPrototype::BASE_COST[PrototypeType::Heavy] >= 0) {
								result.push_back(PrototypeType::Heavy);
								++heavies[player];
								gold -= SoldierPrototype::BASE_COST[PrototypeType::Heavy];
							} else {
								noMoneyLeft = true;
							}
						} else if (myArtilleryCounterPower <= goodCounterRatio) {
							if (gold - SoldierPrototype::BASE_COST[PrototypeType::Infantry] >= 0) {
								result.push_back(PrototypeType::Infantry);
								++infantries[player];
								gold -= SoldierPrototype::BASE_COST[PrototypeType::Infantry];
							} else {
								noMoneyLeft = true;
							}
						
						}
					} else {
						
						if (heavy > artillery) { //h a i
							if (myHeavyCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Artillery] >= 0) {
									result.push_back(PrototypeType::Artillery);
									++artilleries[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Artillery];
								} else {
									noMoneyLeft = true;
								}
							}else if (myArtilleryCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Infantry] >= 0) {
									result.push_back(PrototypeType::Infantry);
									++infantries[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Infantry];
								} else {
									noMoneyLeft = true;
								}
							}
							else if (myInfantryCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Heavy] >= 0) {
									result.push_back(PrototypeType::Heavy);
									++heavies[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Heavy];
								} else {
									noMoneyLeft = true;
								}
							}
							
						} else { //a h i
							if (myArtilleryCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Infantry] >= 0) {
									result.push_back(PrototypeType::Infantry);
									++infantries[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Infantry];
								} else {
									noMoneyLeft = true;
								}
							} else if (myHeavyCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Artillery] >= 0) {
									result.push_back(PrototypeType::Artillery);
									++artilleries[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Artillery];
								} else {
									noMoneyLeft = true;
								}
							} else if (myInfantryCounterPower <= goodCounterRatio) {
								if (gold - SoldierPrototype::BASE_COST[PrototypeType::Heavy] >= 0) {
									result.push_back(PrototypeType::Heavy);
									++heavies[player];
									gold -= SoldierPrototype::BASE_COST[PrototypeType::Heavy];
								} else {
									noMoneyLeft = true;
								}
							} 
						}
					}
				}
				
				myArtilleryCounterPower = (infantries[player] + 1) / (artillery + 1);
				myInfantryCounterPower = (heavies[player] + 1) / (infantry + 1);
				myHeavyCounterPower = (artilleries[player] + 1) / (heavy + 1);
				
				biggerArmy = myInfantryCounterPower >= goodCounterRatio && 
					myHeavyCounterPower >= goodCounterRatio && 
					myArtilleryCounterPower >= goodCounterRatio;
			}
		}
		return result;
	}
	
	bool compareTownValues(const QPair<Town *, SNTypes::heur> &f1, const QPair<Town *, SNTypes::heur> &f2) 
	{
		return f1.second < f2.second;
	}
	
	QMap<Town *, PrototypeType> buildHeuristic(Player* player)
	{
		QList<PrototypeType> prototypesToBuy = whichUnitsCreate(player);
		qDebug() << prototypesToBuy.size();
		QMap<Town *, PrototypeType> result;
		if (!prototypesToBuy.isEmpty()) {
			QList<QPair<Town *, SNTypes::heur>> townSoldierValues;
			QList<QPair<Town *, SNTypes::heur>> townSettlerValues;
			Town *townSettler = nullptr;
			
			if (prototypesToBuy.first() == PrototypeType::Settler) {
				for (Town *town: player->towns()) 
					if (town->tile()->unit() == nullptr) 
						townSettlerValues.push_back(qMakePair(town, townCreateSettlerHeuristic(town)));
				
				qSort(townSettlerValues.begin(), townSettlerValues.end(), compareTownValues);
				result.insert(townSettlerValues.first().first, PrototypeType::Settler);
				townSettler = townSettlerValues.first().first;
				prototypesToBuy.pop_front();
			}
			
			for (Town *town: player->towns()) 
				if (town->tile()->unit() == nullptr) 
					if (town != townSettler)
						townSoldierValues.push_back(qMakePair(town, townCreateSoldierHeuristic(town)));
			
			qSort(townSoldierValues.begin(), townSoldierValues.end(), compareTownValues);
			for (PrototypeType type: prototypesToBuy) {
				result.insert(townSoldierValues.first().first, type);
				townSoldierValues.pop_front();
			}
		} 
		return result;
	}
	
	BonusType whichTechnologyPath(Player* player)
	{
		int otherUnits = 0;
		QList<Player *> players = GameManager::get()->players();
		for(Player *other: players) 
			if (other != player)
				otherUnits += player->getUnitsCount();
		qreal ratio = otherUnits != 0 ? (player->getUnitsCount() * 3) / otherUnits : std::numeric_limits<qreal>::max();
		if (ratio < defensePathRatio)
			return BonusType::Def;
		if (ratio >= warfarePathRatio)
			return BonusType::War;
		return BonusType::Eco;
	}
}
