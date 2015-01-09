#ifndef SOLDIERPROTOTYPE_HPP
#define SOLDIERPROTOTYPE_HPP

#include "Prototype.hpp"

class SoldierPrototype : public Prototype {
public:
	static const QHash<PrototypeType, SNTypes::ap> ACTION_POINTS;
	static const QHash<PrototypeType, SNTypes::amount> BASE_COST;
	static const QHash<PrototypeType, QString> BASE_NAME;
	static const QHash<PrototypeType, SNTypes::hp> BASE_HEALTH;
	static const QHash<PrototypeType, SNTypes::distance> BASE_ATTACK_RANGE;
	static const QHash<PrototypeType, SNTypes::ap> BASE_ATTACK_COST;
	static const QHash<PrototypeType, SNTypes::dmg> BASE_DAMAGE;

	SoldierPrototype(PrototypeType type, const QString &name, SNTypes::ap actionPoints, SNTypes::amount cost,
		SNTypes::hp health, SNTypes::ap attackCost, SNTypes::distance attackRange, SNTypes::dmg damage);
	SoldierPrototype(PrototypeType type);
	~SoldierPrototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) override;
	
	SNTypes::ap attackCost() const;
	void setAttackCost(SNTypes::ap attackCost);
	
	SNTypes::distance attackRange() const;
	void setAttackRange(SNTypes::distance attackRange);
	
	SNTypes::dmg damage() const;
	void setDamage(SNTypes::dmg damage);

private:
	SNTypes::ap attackCost_;
	SNTypes::distance attackRange_;
	SNTypes::dmg damage_;
};

#endif
