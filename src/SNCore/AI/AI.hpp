#ifndef AI_MODULE_HPP
#define AI_MODULE_HPP
#include <limits>

class Tile;
class Player;
class Unit;

namespace AI {
	QSet<Tile *> getAllTargets(Player *player);
	Tile *evaluate(Player *player, Unit *unit, int (*heuristic)(Unit *,Tile *));
}

#endif