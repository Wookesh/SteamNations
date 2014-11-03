#include "GameView.hpp"
#include <QTouchEvent>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
	QGraphicsScene *scene = new QGraphicsScene();
	scene->addRect(QRect(100, 100, 200, 200));
	QPolygonF hexagon;
	for (int i = 0; i < 6; ++i)
		hexagon << QPointF(50 * cos(2 * 3.14 / 6 * i), 50 * sin(2 * 3.14 / 6 * i));
	QGraphicsPolygonItem *pol = scene->addPolygon(hexagon);
	setScene(scene);
}

bool GameView::event(QEvent *e)
{
	return QGraphicsView::event(e);
}
