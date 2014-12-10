#ifndef SOLDIERPROTOTYPE_HPP
#define SOLDIERPROTOTYPE_HPP

#include "Prototype.hpp"

class SoldierPrototype : public Prototype {
public:
	static const QHash<PrototypeType, SNTypes::ap> ACTION_POINTS;
	static const QHash<PrototypeType, SNTypes::amount> BASE_COST;
	static const QHash<PrototypeType, QString> BASE_NAME;
	static const QHash<PrototypeType, SNTypes::hp> BASE_HEALTH;

	SoldierPrototype(PrototypeType type, const QString &name, SNTypes::ap actionPoints, SNTypes::amount cost, SNTypes::hp health);
	SoldierPrototype(PrototypeType type);
	~SoldierPrototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) override;

private:
	SNTypes::dmg damage_;
};

#endif
