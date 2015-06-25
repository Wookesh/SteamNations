#ifndef SOLDIER_HPP
#define SOLDIER_HPP
#include "Unit.hpp"

class SoldierPrototype;
class Tile;
class Town;

class Soldier : public Unit {
Q_OBJECT
public:
	Soldier(Tile *tile, const SoldierPrototype *prototype, Player *owner, QObject *parent = nullptr);
	
	bool canCapture(const Tile *currTile) const;
	bool capture(Town *town, unsigned int captureCost);
	
	bool canAttack(const Tile *currTile) const;
	bool attack(Unit *unit);
	
	bool canPerform(ActionType, const Tile *tile) const override;
	float attackBonus(Soldier *soldier);
	
	SNTypes::ap attackCost() const;
	SNTypes::distance attackRange() const;
	SNTypes::distance ctrAtkRange() const;
	SNTypes::dmg damage() const;
	
	virtual void getAttacked(Soldier *) override;
	virtual void updateBefore() override;
protected:
	virtual ActionType getActionType(Tile *tile) override;
};


#endif
