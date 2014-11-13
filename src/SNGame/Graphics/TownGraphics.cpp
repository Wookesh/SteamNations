#include "TownGraphics.hpp"
#include "../../SNCore/Tile.hpp"
#include "../SNHelpers.hpp"
#include <QPainter>
#include <QDebug>

TownGraphics::TownGraphics(const Town *town, QGraphicsItem *parent) : 
	QGraphicsRectItem(coordToPos(town->tile()->position()).x() - SIZE / 2,
	coordToPos(town->tile()->position()).y() - SIZE / 2 , SIZE, SIZE, parent), town_(town)
{
	setZValue(1);
}

TownGraphics::~TownGraphics()
{
	
}

void TownGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = painter->pen();
	pen.setBrush(Qt::lightGray);
	pen.setWidth(5);
	painter->setPen(pen);
	painter->drawRoundedRect(boundingRect(), 20.0, 20.0);
	pen.setWidth(30);
	pen.setColor(Qt::black);
	painter->setPen(pen);
	painter->drawText(QRect(boundingRect().x() + SIZE / 4, boundingRect().y() + SIZE / 4,
		SIZE / 2, SIZE / 2), town_->name());
}
