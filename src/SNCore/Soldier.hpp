#ifndef SOLDIER_HPP
#define SOLDIER_HPP
#include "Unit.hpp"

class Town;

class Soldier : public Unit {
Q_OBJECT
public:
	Soldier(Tile *tile, const Prototype *prototype, QObject *parent = nullptr);
	
	bool canCapture(Tile *currTile);
	bool captuer(Town *town);
	
	bool canAttack(Tile *currTile);
	bool attack(Unit *unit);
};


#endif