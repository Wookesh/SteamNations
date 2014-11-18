#ifndef SOLDIERPROTOTYPE_HPP
#define SOLDIERPROTOTYPE_HPP

#include "Prototype.hpp"

class SoldierPrototype : public Prototype {
public:
	SoldierPrototype(const QString &name = BASE_NAME, int moveRange = BASE_MOVERANGE, int cost = BASE_COST);
	~SoldierPrototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) override;
	
	static const QString BASE_NAME;
	static const int BASE_MOVERANGE = 2;
	static const int BASE_COST = 0;
};

#endif
