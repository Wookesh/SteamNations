#include "UnitGraphics.hpp"
#include "../SNCore/Tile.hpp"
#include "SNHelpers.hpp"
#include <QPainter>

UnitGraphics::UnitGraphics(const Unit *unit, QGraphicsItem *parent) :  
	QGraphicsRectItem( -SIZE / 2, -SIZE / 2, SIZE, SIZE, parent), unit_(unit)
{
	setPos(coordToPos(unit->tile()->position()).x(), coordToPos(unit->tile()->position()).y());
	setZValue(2);
}

UnitGraphics::~UnitGraphics()
{
	
}

void UnitGraphics::updatePosition()
{
	setPos(coordToPos(unit_->tile()->position()).x(),
		coordToPos(unit_->tile()->position()).y());
	update();
}


void UnitGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = painter->pen();
	pen.setBrush(Qt::darkRed);
	pen.setWidth(5);
	painter->setPen(pen);
	painter->drawRoundedRect(boundingRect(), 20.0, 20.0);
	pen.setWidth(30);
	pen.setColor(Qt::black);
	painter->setPen(pen);
	painter->drawText(QRect(boundingRect().x() + SIZE / 4, boundingRect().y() + SIZE / 4,
		SIZE / 2, SIZE / 2), unit_->name());
}

void UnitGraphics::animate(Action *action)
{

}

