#include "InfoBox.hpp"
#include "SNCore/Objects/Object.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Console.hpp"
#include "SNCore/Objects/Unit.hpp"
#include <QDebug>

InfoBox::InfoBox(QObject* parent): QObject(parent), visible_(false), selectedObject_(nullptr)
{

}

void InfoBox::setVisible(bool visible)
{
	visible_ = visible;
	emit visibleChanged();
}

bool InfoBox::visible()
{
	return visible_;
}

QString InfoBox::name()
{
	return selectedObject_ ? selectedObject_->name() : "undefined";
}

QString InfoBox::owner()
{
	return selectedObject_ ? selectedObject_->owner()->name() : "undefined";
}


void InfoBox::setObject(const Object* object)
{
	selectedObject_ = object;
	emit objectChanged();
	
	if(object->type() == ObjectType::Unit)
		emit unitChanged();
}

QStringList &InfoBox::actions()
{
	return objectActions_;
}

void InfoBox::setActions(QStringList &actions)
{
	objectActions_ = actions;
}

qint16 InfoBox::healthLeft()
{
	if(selectedObject_->type() == ObjectType::Unit) 
		return (qint16)static_cast<const Unit*>(selectedObject_)->healthLeft();
	return 0;
}

qint16 InfoBox::health()
{
	if(selectedObject_->type() == ObjectType::Unit)
		return (qint16)static_cast<const Unit*>(selectedObject_)->health();
	return 0;
}
