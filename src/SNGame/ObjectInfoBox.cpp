#include "ObjectInfoBox.hpp"
#include <qlocale.h>
#include <QPaintEvent>
#include <QPainter>

ObjectInfoBox::ObjectInfoBox(QWidget *parent) : QWidget(parent)
{
	nameDisplay_ = new QLabel(tr("Object Name"), this);
	nameDisplay_->setGeometry(0, 0, sizeHint().width(), 50);
}

ObjectInfoBox::~ObjectInfoBox()
{
	
}

void ObjectInfoBox::setObject(const Object *object, const QVector<Action *> &actions)
{
	nameDisplay_->setText(object->name());
	switch (object->type()) {
		case Unit::Type::Town: {
			break;
		}
		case Unit::Type::Unit: {
			break;
		}
	}
}

QSize ObjectInfoBox::minimumSizeHint() const
{
	return ObjectInfoBox::sizeHint();
}

QSize ObjectInfoBox::sizeHint() const
{
	return QSize(200, 500);
}

void ObjectInfoBox::paintEvent(QPaintEvent *e)
{
	QPainter *painter = new QPainter(this);
	painter->fillRect(0,0, size().width(), size().height(), QBrush(Qt::darkGray));
}


