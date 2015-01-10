#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <QtQuick/QQuickItem>
#include <QColor>
#include <QImage>
#include <QHash>


class BoardField;
class QQuickWindow;
class TextureManager;
class Object;
class Action;
class Tile;
class ActionType;

class GameBoard : public QQuickItem {
Q_OBJECT
public:
	static const int INTERVAL = 250;
	qreal SHADOW_OPACITY = 0.2;
	GameBoard(QQuickItem *parent = 0);
	Q_INVOKABLE void click(int mouseX, int mouseY, int x, int y, float scale);

protected:
	QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
private:
	static QTimer *timer_;
	TextureManager *textureManager_;
	const Object *selectedObject_;
	
	QVector<Action *> mapActions_;
	QVector<Action *> objectActions_;
	
	void select(Tile *tile);
	QHash<int,BoardField *> nodeMap;

	int index(int x, int y);
	void initTimer();

	const qreal GBcos(int i);
	const qreal GBsin(int i);
	
	QPoint pixelToHex(int x, int y);
	static const QColor highlightColor(ActionType actionType);
	
	void getActions();
	void clearActions();
private slots:
	void nextFrame();
public slots:
	void clearSelect();
signals:
	void selectionUpdate();
	void noSelection();
};
#endif // GAMEBOARD_HPP




