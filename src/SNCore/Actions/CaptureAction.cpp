#include "CaptureAction.hpp"
#include "../Objects/Town.hpp"
#include "../Objects/Soldier.hpp"

CaptureAction::CaptureAction(Soldier *mainObject, Town *town, unsigned int captureCost): 
	Action(mainObject, town->tile(), ActionType::Capture), town_(town), captureCost_(captureCost)
{

}

bool CaptureAction::perform()
{
	return dynamic_cast<Soldier *>(mainObject_)->capture(town_, captureCost_);;
}

unsigned int CaptureAction::captureCost() {
	return captureCost_;
}
