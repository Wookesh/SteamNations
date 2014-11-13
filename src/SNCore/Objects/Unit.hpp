#ifndef UNIT_HPP
#define UNIT_HPP

#include "Object.hpp"
#include "Prototypes/Prototype.hpp"

class Prototype;

class Unit : public Object {
Q_OBJECT
public:
    Unit(Tile *tile, const Prototype *prototype, Player *owner, QObject *parent = nullptr);
	virtual ~Unit();
	
	virtual void updateBefore() override;
	virtual void updateAfter() override;
	
	virtual QString name() const override;
	
	Prototype::Type pType() const;
	
	quint8 moveRange() const;
	quint8 currentMoveRange() const;
	
	bool canMove(const Tile *tile) const;
	bool move(Tile *tile);
	virtual void getAttacked(Unit *) = 0;
protected:
	const Prototype *prototype_;
	quint8 currentMoveRange_;
};

#endif
