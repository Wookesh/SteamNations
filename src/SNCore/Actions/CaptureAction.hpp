#ifndef CAPTUREACTION_HPP
#define CAPTUREACTION_HPP

#include "Action.hpp"

class Town;
class Soldier;

class CaptureAction : public Action {
public :
	CaptureAction(Soldier *mainObject, Town *town, unsigned int captureCost);
	
	virtual bool perform();
	unsigned int captureCost();
protected:
	Town *town_;
	unsigned int captureCost_;
};


#endif