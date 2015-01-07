#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <QtQuick/QQuickItem>
#include <QColor>
#include <QImage>
#include <QHash>


class BoardField;
class QQuickWindow;
class TextureManager;

class GameBoard : public QQuickItem {
Q_OBJECT
public:
	GameBoard(QQuickItem *parent = 0);
	Q_INVOKABLE void click(int mouseX, int mouseY, int x, int y, float scale);

protected:
	QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
private:
	static QTimer *timer_;
	QHash<int,BoardField *> nodeMap;

	int index(int x, int y);
	void initTimer();

	TextureManager *textureManager_;
private slots:
	void nextFrame();
};
#endif // GAMEBOARD_HPP




