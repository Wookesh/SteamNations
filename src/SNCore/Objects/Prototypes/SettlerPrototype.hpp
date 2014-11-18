#ifndef SETTLERPROTOTYPE_HPP
#define SETTLERPROTOTYPE_HPP

#include "Prototype.hpp"

class SettlerPrototype : public Prototype {
public:
	SettlerPrototype(const QString &name = BASE_NAME, int moveRange = BASE_MOVERANGE, int cost = BASE_COST);
	~SettlerPrototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) override;
	
	static const QString BASE_NAME;
	static const int BASE_MOVERANGE = 2;
	static const int BASE_COST = 0;
};

#endif
