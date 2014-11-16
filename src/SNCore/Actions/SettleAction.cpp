#include "SettleAction.hpp"
#include "../Objects/Settler.hpp"

SettleAction::SettleAction(Settler *mainObject) : Action(mainObject, mainObject->tile(), ActionType::Settle)
{
	
}


bool SettleAction::perform()
{
	return dynamic_cast<Settler *>(mainObject_)->settle();
}
