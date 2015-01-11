#include "InfoBox.hpp"

InfoBox::InfoBox(QObject* parent) : visible_(false)
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
	return name_;
}

QString InfoBox::owner()
{
	return owner_;
}

void InfoBox::setName(QString name)
{
	name_ = name;
	emit nameChanged();
}

void InfoBox::setOwner(QString owner)
{
	owner_ = owner;
	emit ownerChanged();
}
