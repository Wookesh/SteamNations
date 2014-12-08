#ifndef BOARD_HPP
#define BOARD_HPP

#include <QtQuick/QQuickItem>
#include <QColor>
#include <QImage>
#include<QHash>


class Board : public QQuickItem {
Q_OBJECT
public:
	Board(QQuickItem *parent = 0);

protected:
	QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
private:
	static QTimer *timer_;
	QHash<int,QSGNode *> nodeMap;

	int index(int x, int y);
	void initTimer();

private slots:
	void nextFrame();
};
#endif // BOARD_HPP




