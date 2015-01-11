#ifndef WARFAREBONUSES_HPP
#define WARFAREBONUSES_HPP

#include "Bonus.hpp"

class Soldier;

class WarfareT1Bonus : public Bonus {
public :
	WarfareT1Bonus (Player *player);
	
	virtual bool apply();
};


#endif