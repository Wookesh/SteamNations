#include "CaptureAction.hpp"
#include "../Objects/Town.hpp"
#include "../Objects/Soldier.hpp"
#include "GameManager.hpp"
#include <Board.hpp>

CaptureAction::CaptureAction(Soldier *mainObject, Town *town): 
	Action(mainObject, town->tile(), ActionType::Capture), town_(town)
{
	captureCost_ = GameManager::get()->board()->getDistance(mainObject_->tile(), town->tile());
}

bool CaptureAction::perform()
{
	return dynamic_cast<Soldier *>(mainObject_)->capture(town_, captureCost_);;
}

unsigned int CaptureAction::captureCost() {
	return captureCost_;
}
