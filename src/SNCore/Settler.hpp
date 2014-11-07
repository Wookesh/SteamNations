#ifndef SETTLER_HPP
#define SETTLER_HPP

#include "Unit.hpp"

class SettlerPrototype;
class Town;

class Settler : public Unit {
public:
	Settler(Tile *tile, const SettlerPrototype *prototype, QObject *parent = nullptr);
	~Settler();
	
	Town *createTown();
	
	virtual void getAttacked(Unit *) override;
private:
signals:
	void cityCreated();
};

#endif
