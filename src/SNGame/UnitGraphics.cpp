#include "UnitGraphics.hpp"

UnitGraphics::UnitGraphics(Unit *unit): QGraphicsPolygonItem() , unit_(unit)
{
	
}

UnitGraphics::~UnitGraphics()
{

}

void UnitGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPolygonItem::paint(painter, option, widget);
}

void UnitGraphics::animate(SN::Action action)
{

}

