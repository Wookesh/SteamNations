#include "CaptureAction.hpp"
#include "../Objects/Town.hpp"
#include "../Objects/Soldier.hpp"

CaptureAction::CaptureAction(Soldier *mainObject, Town *town): 
	Action(mainObject, town->tile(), Type::Capture), town_(town)
{

}

bool CaptureAction::perform()
{
	return dynamic_cast<Soldier *>(mainObject_)->capture(town_);
}
