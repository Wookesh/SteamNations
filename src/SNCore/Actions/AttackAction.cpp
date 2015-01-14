#include "AttackAction.hpp"
#include "../Objects/Soldier.hpp"


AttackAction::AttackAction(Soldier *mainObject, Unit *target) : 
	Action(mainObject, target->tile(), ActionType::Attack),
	target_(target)
{
	
}

bool AttackAction::perform()
{
	Soldier *soldier = dynamic_cast<Soldier *>(mainObject_);
	
	bool result = soldier->attack(target_);

	if (soldier->checkForDeath())
		delete soldier;
	
	if (target_->checkForDeath())
		delete target_;
	
	return result;
}
