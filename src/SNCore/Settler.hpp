#ifndef SETTLER_HPP
#define SETTLER_HPP

#include "Unit.hpp"
#include "SettlerPrototype.hpp"
class Town;

class Settler : public Unit {
public:
	Settler(const SettlerPrototype *prototype, QObject *parent = nullptr);
	~Settler();
	
	Town *createTown();
private:
};

#endif
