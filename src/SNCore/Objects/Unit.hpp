#ifndef UNIT_HPP
#define UNIT_HPP

#include "Object.hpp"
#include "Prototypes/Prototype.hpp"
#include "SNCore/Actions/Action.hpp"

class Prototype;
class Soldier;
class Tile;

class Unit : public Object {
Q_OBJECT
public:
	Unit(Tile *tile, const Prototype *prototype, Player *owner, SNTypes::heur (*heuristic)(Unit *, Tile *), QObject *parent = nullptr);
	virtual ~Unit();
	
	virtual void updateBefore() override;
	virtual void updateAfter() override;
	
	virtual QString name() const override;
	
	PrototypeType pType() const;
	
	SNTypes::ap actionPoints() const;
	SNTypes::ap actionPointsLeft() const;
	
	SNTypes::hp health() const;
	SNTypes::hp healthLeft() const;
	
	SNTypes::distance visionRange() const;
	
	bool canMove(const Tile *tile) const;
	
	virtual bool canPerform(ActionType action, const Tile *tile) const;
	
	bool move(Tile *tile, SNTypes::ap moveCost);
	virtual void getAttacked(Soldier *) = 0;
	void removeHealth(SNTypes::dmg);
	bool checkForDeath();
	
	void updateVision();
	
	bool load(QDataStream &in);
	bool save(QDataStream &out);
	
	Tile *findBestTarget();
	QPair<ActionType, Tile *> getTargetWithAction();
protected:
	const Prototype *prototype_;
	SNTypes::ap actionPointsLeft_;
	SNTypes::hp healthLeft_;
	
	void spentActionPoints(SNTypes::ap actionPoints);
	virtual ActionType getActionType(Tile *tile) = 0;
	SNTypes::heur (*heuristic_)(Unit *, Tile *);
};

#endif
