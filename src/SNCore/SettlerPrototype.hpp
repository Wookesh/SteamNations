#ifndef SETTLERPROTOTYPE_HPP
#define SETTLERPROTOTYPE_HPP

#include "Prototype.hpp"

class SettlerPrototype : public Prototype {
public:
	SettlerPrototype(const QString &name, int moveRange, int cost);
	~SettlerPrototype();
private:
};

#endif
