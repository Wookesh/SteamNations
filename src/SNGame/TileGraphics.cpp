#include "TileGraphics.hpp"

TileGraphics::TileGraphics(Tile *tile): QGraphicsPolygonItem() , tile_(tile)
{
	
}

TileGraphics::~TileGraphics()
{
	
}

void TileGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void TileGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void TileGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPolygonItem::paint(painter, option, widget);
}

void TileGraphics::highlight(SN::Action action)
{

}

