#include "TileGraphics.hpp"
#include "SNScene.hpp"

#include <QGraphicsSceneMouseEvent>

TileGraphics::TileGraphics(Tile *tile): QGraphicsPolygonItem() , tile_(tile)
{
	
}

TileGraphics::~TileGraphics()
{
	
}

void TileGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		pressed_ = true;
	QGraphicsItem::mousePressEvent(event);
}

void TileGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		if (pressed_)
				dynamic_cast<SNScene *>(scene())->select(tile_);
		pressed_ = false;
	}
	QGraphicsItem::mouseReleaseEvent(event);
}

void TileGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPolygonItem::paint(painter, option, widget);
}

void TileGraphics::highlight(SN::Action action)
{
}

