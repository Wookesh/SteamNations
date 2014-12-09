#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <QtQuick/QQuickItem>
#include <QColor>
#include <QImage>
#include<QHash>

class BoardField;

class GameBoard : public QQuickItem {
Q_OBJECT
public:
	GameBoard(QQuickItem *parent = 0);

protected:
	QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
private:
	static QTimer *timer_;
	QHash<int,BoardField *> nodeMap;

	int index(int x, int y);
	void initTimer();

private slots:
	void nextFrame();
};
#endif // GAMEBOARD_HPP




