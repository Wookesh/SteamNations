#ifndef ECONOMYBONUSES_HPP
#define ECONOMYBONUSES_HPP

#include "Bonus.hpp"


/*
 * Tier1
 */

class EconomyT1Bonus : public Bonus {
public :
	EconomyT1Bonus();
	
	virtual bool apply(Player *player);
};

/*
 * Tier2
 */

class EconomyT2Bonus : public Bonus {
public :
	EconomyT2Bonus();
	
	virtual bool apply(Player *player);
};

/*
 * Tier3
 */

class EconomyT3Bonus : public Bonus {
public :
	EconomyT3Bonus();
	
	virtual bool apply(Player *player);
};



#endif