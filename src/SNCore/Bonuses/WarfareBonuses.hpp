#ifndef WARFAREBONUSES_HPP
#define WARFAREBONUSES_HPP

#include "Bonus.hpp"

class Soldier;

/*
 * Tier1
 */

class WarfareT1Bonus : public Bonus {
public :
	WarfareT1Bonus();
	
	virtual bool apply(Player *player);
};

/*
 * Tier2
 */

class WarfareT2Bonus : public Bonus {
public :
	WarfareT2Bonus();
	
	virtual bool apply(Player *player);
};

/*
 * Tier3
 */

class WarfareT3Bonus : public Bonus {
public :
	WarfareT3Bonus();
	
	virtual bool apply(Player *player);
};



#endif