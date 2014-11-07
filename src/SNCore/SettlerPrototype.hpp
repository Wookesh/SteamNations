#ifndef SETTLERPROTOTYPE_HPP
#define SETTLERPROTOTYPE_HPP

#include "Prototype.hpp"

const QString BASE_SETTLER_NAME = "Settler";
const int BASE_SETTLER_MOVERANGE = 2;
const int BASE_SETTLER_COST = 0;

class SettlerPrototype : public Prototype {
public:
	SettlerPrototype(const QString &name, int moveRange, int cost);
	~SettlerPrototype();
	
	virtual Unit *createUnit(Tile *tile) override;
private:
};

#endif
