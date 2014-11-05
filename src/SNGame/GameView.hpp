#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QEvent>

class GameView : public QGraphicsView {
Q_OBJECT
public:
	GameView(QWidget *parent = nullptr);
protected:
	bool event(QEvent *e);
	virtual void wheelEvent(QWheelEvent *event);
private:
	bool pressed_;
	QPoint startingPos_;
	QPointF startingPosScene_;
};

#endif
