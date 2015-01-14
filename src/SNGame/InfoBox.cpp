#include "InfoBox.hpp"
#include "SNCore/Objects/Object.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/GameManager.hpp"
#include "SNCore/Console.hpp"

InfoBox::InfoBox(QObject* parent) : visible_(false), selectedObject_(nullptr)
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
}

QStringList &InfoBox::actions()
{
	return objectActions_;
}

void InfoBox::setActions(QStringList &actions)
{
	objectActions_ = actions;
}

