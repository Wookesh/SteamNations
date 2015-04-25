#include "AttackAction.hpp"
#include "../Objects/Soldier.hpp"
#include "GameManager.hpp"
#include "Console.hpp"


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
	
	if (target_->checkForDeath()) {
		if (target_->pType() == PrototypeType::Settler) {
			delete target_;
			GameManager::get()->checkIfWin(soldier->owner(), WinCondition::Conquest);
		} else {
			delete target_;				
		}
	}
	
	return result;
}
