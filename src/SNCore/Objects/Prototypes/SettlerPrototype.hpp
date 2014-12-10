#ifndef SETTLERPROTOTYPE_HPP
#define SETTLERPROTOTYPE_HPP

#include "Prototype.hpp"

class SettlerPrototype : public Prototype {
public:
	SettlerPrototype(const QString &name = BASE_NAME, SNTypes::ap actionPoints = BASE_MOVERANGE,
		SNTypes::amount cost = BASE_COST, SNTypes::hp health = BASE_HEALTH);
	~SettlerPrototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) override;
	
	static const QString BASE_NAME;
	static const SNTypes::ap BASE_MOVERANGE = 2;
	static const SNTypes::amount BASE_COST = 0;
	static const SNTypes::hp BASE_HEALTH = 20;
};

#endif
