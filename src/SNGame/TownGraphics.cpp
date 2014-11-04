#include "TownGraphics.hpp"

TownGraphics::TownGraphics(Town *town): QGraphicsPolygonItem() , town_(town)
{

}

TownGraphics::~TownGraphics()
{

}

void TownGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPolygonItem::paint(painter, option, widget);
}

