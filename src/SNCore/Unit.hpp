#ifndef UNIT_HPP
#define UNIT_HPP

#include "Object.hpp"

class Prototype;

class Unit : public Object {
Q_OBJECT
public:
	Unit(const Prototype *prototype, QObject *parent = nullptr);
	virtual ~Unit();
	
	virtual void updateBefore() override;
	virtual void updateAfter() override;
	
	bool move(Tile *tile);
	void getAttacked(Unit *);
protected:
	const Prototype *prototype_;
signals:
	void unitDestroyed();
};

#endif
