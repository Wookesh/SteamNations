#ifndef SETTLER_HPP
#define SETTLER_HPP

#include "Unit.hpp"

class SettlerPrototype;
class Town;

class Settler : public Unit {
Q_OBJECT
public:
    Settler(Tile *tile, const SettlerPrototype *prototype, Player *owner, QObject *parent = nullptr);
	~Settler();
	
	bool canSettle(Tile *tile) const;
	bool settle();
	Town *createTown();
	
	virtual void getAttacked(Unit *) override;
signals:
	void cityCreated();
};

#endif
