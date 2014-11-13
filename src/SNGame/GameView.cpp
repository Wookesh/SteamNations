#include "GameView.hpp"
#include "Graphics/TileGraphics.hpp"
#include "Graphics/TownGraphics.hpp"
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
	//setRenderHint(QPainter::Antialiasing);
	setOptimizationFlag(QGraphicsView::DontSavePainterState);
	setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
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
