#include "CaptureAction.hpp"
#include "Town.hpp"
#include "Soldier.hpp"

CaptureAction::CaptureAction(Soldier *mainObject, Town *town): 
	Action(mainObject, town->tile(), Type::Capture), town_(town)
{

}

bool CaptureAction::perform()
{
	return dynamic_cast<Soldier *>(mainObject)->capture(town_);
}
