#include "CreateUnitAction.hpp"
#include "../Objects/Prototypes/Prototype.hpp"
#include "../Objects/Town.hpp"
#include "../Objects/Unit.hpp"
#include <QDebug>

CreateUnitAction::CreateUnitAction(Town *town, Prototype::Type type): Action(town, town->tile(), Type::CreateUnit), type_(type)
{

}

bool CreateUnitAction::perform()
{
	qDebug() << "perform leci";
	Unit *unit = dynamic_cast<Town *>(mainObject_)->createUnit(type_);
	return unit != nullptr;
}

Prototype::Type CreateUnitAction::pType()
{
	return type_;
}
