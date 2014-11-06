#include "GameView.hpp"
#include "TileGraphics.hpp"
#include "TownGraphics.hpp"
#include <QTouchEvent>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QScrollBar>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setDragMode(QGraphicsView::ScrollHandDrag);
	setRenderHint(QPainter::Antialiasing);
	setOptimizationFlag(QGraphicsView::DontSavePainterState);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	QGraphicsScene *scene = new QGraphicsScene();
	for (int i = 0; i < 50; ++i) {
		
		qreal k = (i % 2 == 0 ? 0 : 120);
		
		for (int j = 0; j < 25; ++j) {
			TileGraphics *tile = new TileGraphics(nullptr);
			tile->setPos(j * 240 + k, i * 40 * sqrt(3));
			scene->addItem(tile);
		}
	}
	setScene(scene);
}

bool GameView::event(QEvent *e)
{
	return QGraphicsView::event(e);
}

void GameView::wheelEvent(QWheelEvent* event)
{
	mapToScene(event->pos());
	qreal factor = std::pow(1.0005, event->delta());
	if((factor > 1 && transform().m11() < maxZoom) || (factor < 1 && transform().m11() > minZoom))
		scale(factor, factor);
}
