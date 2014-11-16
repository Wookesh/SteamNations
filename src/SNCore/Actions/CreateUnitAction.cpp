#include "CreateUnitAction.hpp"
#include "../Objects/Prototypes/Prototype.hpp"
#include "../Objects/Town.hpp"
#include "../Objects/Unit.hpp"
#include <QDebug>

CreateUnitAction::CreateUnitAction(Town *town, ProtoType type): Action(town, town->tile(), ActionType::CreateUnit), type_(type)
{

}

bool CreateUnitAction::perform()
{
	qDebug() << "perform leci";
	Unit *unit = dynamic_cast<Town *>(mainObject_)->createUnit(type_);
	return unit != nullptr;
}

ProtoType CreateUnitAction::pType()
{
	return type_;
}
