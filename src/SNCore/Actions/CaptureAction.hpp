#ifndef CAPTUREACTION_HPP
#define CAPTUREACTION_HPP
#include "Action.hpp"

class Town;
class Soldier;

class CaptureAction : public Action {
public :
	CaptureAction(Soldier *mainObject, Town *town);
	
	virtual bool perform();
protected:
	Town *town_;
};


#endif