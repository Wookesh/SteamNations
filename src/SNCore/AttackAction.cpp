#include "AttackAction.hpp"
#include "Unit.hpp"

AttackAction::AttackAction(Soldier *mainObject, Unit *target): Action(mainObject, target->tile(), Type::Attack)
{
	
}

bool AttackAction::perform()
{
	return dynamic_cast<Soldier *>(mainObject_)->canAttack(tile_);
}
