#include "SettleAction.hpp"
#include "../Objects/Settler.hpp"

SettleAction::SettleAction(Settler *mainObject) : Action(mainObject, mainObject->tile(), ActionType::Settle)
{
	
}


bool SettleAction::perform()
{
	bool result = dynamic_cast<Settler *>(mainObject_)->settle();
	
	if (result)
		delete mainObject_;
		
	return result;
}
