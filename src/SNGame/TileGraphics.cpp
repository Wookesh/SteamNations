#include "TileGraphics.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include "SNScene.hpp"
#include "SNHelpers.hpp"

QPolygonF &TileGraphics::hexagon()
{
	static QPolygonF hexagon_;
	if (hexagon_.size() == 0)
		for (int i = 0; i < 6; ++i)
			hexagon_ << QPointF(RADIUS * cos(2 * 3.14 / 6 * i), RADIUS * sin(2 * 3.14 / 6 * i));
	return hexagon_;
}



TileGraphics::TileGraphics(const Tile *tile, QGraphicsItem *parent) : QGraphicsPolygonItem(hexagon(), parent),
tile_(tile)
{
	setPos(coordToPos(tile->position()));
}

TileGraphics::~TileGraphics()
{
	
}

void TileGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
 	qDebug() << "mousePressEvent";
// 	if (event->button() == Qt::LeftButton)
// 		dynamic_cast<SNScene *>(scene())->select(tile_);
	QGraphicsItem::mousePressEvent(event);
}

void TileGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}

void TileGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = painter->pen();
	pen.setWidth(5);
	pen.setColor(Qt::green);
	painter->setPen(pen);
	painter->drawPolygon(polygon(), Qt::OddEvenFill);
	//QGraphicsPolygonItem::paint(painter, option, widget);
}

void TileGraphics::highlight(SN::Action action)
{
}

