#include "TileGraphics.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include "SNScene.hpp"
#include "SNHelpers.hpp"
#include <QMap>

QPolygonF &TileGraphics::hexagon()
{
	static QPolygonF hexagon_;
	if (hexagon_.size() == 0)
		for (int i = 0; i < 6; ++i)
			hexagon_ << QPointF(RADIUS * cos(2 * 3.14 / 6 * i), RADIUS * sin(2 * 3.14 / 6 * i));
	return hexagon_;
}

QColor TileGraphics::highlightColor(Action::Type type)
{
	static QMap<Action::Type, QColor> map({
		{Action::Type::Attack, Qt::red},
		{Action::Type::Capture, Qt::magenta},
		{Action::Type::Move, Qt::cyan},
		{Action::Type::None, Qt::white},
		{Action::Type::Settle, Qt::yellow}
	});
	return map[type];
}

TileGraphics::TileGraphics(const Tile *tile, QGraphicsItem *parent) : QGraphicsPolygonItem(hexagon(), parent),
tile_(tile), actionType_(Action::Type::None)
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
	if (actionType_ != Action::Type::None) {
		QPainterPath path;
		path.addPolygon(polygon());
		painter->setOpacity(OPACITY);
		painter->fillPath(path, highlightColor(actionType_));
	}
}

void TileGraphics::highlight(Action::Type actionType)
{
	actionType_ = actionType;
	update();
}

