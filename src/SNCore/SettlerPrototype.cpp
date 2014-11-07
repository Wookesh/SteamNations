#include "SettlerPrototype.hpp"
#include "Settler.hpp"

SettlerPrototype::SettlerPrototype(const QString &name, int moveRange, int cost) :
	Prototype(name, moveRange, cost)
{

}

SettlerPrototype::~SettlerPrototype()
{

}

Unit *SettlerPrototype::createUnit() {
// 	Settler *settler = new Settler(this);
// 	return settler;
// commented due to changed cosntructor;
}
