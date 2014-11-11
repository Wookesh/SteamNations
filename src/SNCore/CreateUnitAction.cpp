#include "CreateUnitAction.hpp"
#include "Prototype.hpp"
#include "Town.hpp"
#include "Unit.hpp"
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

