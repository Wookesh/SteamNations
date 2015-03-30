#ifndef SETTLERPROTOTYPE_HPP
#define SETTLERPROTOTYPE_HPP

#include "Prototype.hpp"

class SettlerPrototype : public Prototype {
public:
	SettlerPrototype(const QString &name = BASE_NAME, SNTypes::ap actionPoints = BASE_MOVE_RANGE,
		SNTypes::amount cost = BASE_COST, SNTypes::hp health = BASE_HEALTH, SNTypes::distance visionRange = BASE_VISION_RANGE);
	~SettlerPrototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) override;
	
	static const QString BASE_NAME;
	static const SNTypes::ap BASE_MOVE_RANGE = 2;
	static const SNTypes::amount BASE_COST = 200;
	static const SNTypes::hp BASE_HEALTH = 1;
	static const SNTypes::distance BASE_VISION_RANGE = 2;
};

#endif
