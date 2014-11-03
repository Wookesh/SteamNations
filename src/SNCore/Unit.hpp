#ifndef UNIT_HPP
#define UNIT_HPP

#include "Object.hpp"
#include "Prototype.hpp"

class Unit : public Object {
Q_OBJECT
public:
	Unit(const Prototype *prototype, QObject *parent = nullptr);
	virtual ~Unit();
	
	virtual void updateAfter() override;
	
	bool move(Tile *tile);
	void getAttacked(Unit *);
protected:
	const Prototype *prototype_;
signals:
	void unitDesrtoyed();
};

#endif
