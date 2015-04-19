#include "AI.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/Objects/Town.hpp"
#include "SNCore/Objects/Unit.hpp"

#include <QSet>
#include <QVector>

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
		
		tilesToVisit.insert(player->capital()->tile());
		
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
	
	Tile *evaluate(Player *player, Unit *unit, int (*heuristic)(Unit *,Tile *))
	{
		QSet<Tile *> targets = getAllTargets(player);
		QPair<int, Tile *> bestTarget;
		for (Tile *tile: targets) {
			int hVal = heuristic(unit, tile);
			bestTarget = hVal > bestTarget.first ? qMakePair(hVal, tile) : bestTarget;
		}
		return bestTarget.second;
	}
}