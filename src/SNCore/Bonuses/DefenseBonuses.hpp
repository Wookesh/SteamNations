#ifndef DEFENSEBONUSES_HPP
#define DEFENSEBONUSES_HPP

#include "Bonus.hpp"


/*
 * Tier1
 */

class DefenseT1Bonus : public Bonus {
public :
	DefenseT1Bonus();
	
	virtual bool apply(Player *player);
};

/*
 * Tier2
 */

class DefenseT2Bonus : public Bonus {
public :
	DefenseT2Bonus();
	
	virtual bool apply(Player *player);
};

/*
 * Tier3
 */

class DefenseT3Bonus : public Bonus {
public :
	DefenseT3Bonus();
	
	virtual bool apply(Player *player);
};



#endif