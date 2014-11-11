#ifndef SOLDIER_HPP
#define SOLDIER_HPP
#include "Unit.hpp"

class Tile;
class Town;


class Soldier : public Unit {
Q_OBJECT
public:
    Soldier(Tile *tile, const Prototype *prototype, Player *owner, QObject *parent = nullptr);
	
	bool canCapture(Tile *currTile);
	bool capture(Town *town);
	
	bool canAttack(Tile *currTile);
	bool attack(Unit *unit);
};


#endif
