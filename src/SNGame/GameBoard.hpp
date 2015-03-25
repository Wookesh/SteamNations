#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <QtQuick/QQuickItem>
#include <QColor>
#include <QImage>
#include <QHash>
#include "SNCore/Serial.hpp"


class BoardField;
class QQuickWindow;
class TextureManager;
class Object;
class Action;
class Tile;
class ActionType;
class InfoBox;
class BonusManager;

class GameBoard : public QQuickItem {
Q_OBJECT
public:
	static const int INTERVAL = 250;
	qreal SHADOW_OPACITY = 0.2;
	GameBoard(QQuickItem *parent = 0);
	Q_INVOKABLE void click(int mouseX, int mouseY, int x, int y, float scale);
	Q_INVOKABLE void makeAction(int action);
	Q_PROPERTY(InfoBox *infobox READ infobox)
	Q_PROPERTY(BonusManager *bonusManager READ bonusManager)
	Q_PROPERTY(qint16 boardWidth READ boardWidth)
	Q_PROPERTY(qint16 boardHeight READ boardHeight)
	
protected:
	QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
private:
	static QTimer *timer_;
	TextureManager *textureManager_;
	const Object *selectedObject_;
	UID selectedObjectID_;
	InfoBox *infobox_;
	BonusManager *bonusManager_;
	bool boardSet_;
	
	QVector<Action *> mapActions_;
	QVector<Action *> objectActions_;
	InfoBox *infobox();
	BonusManager *bonusManager();
	void select(const Tile *tile);
	QHash<int,BoardField *> nodeMap;

	int index(int x, int y);
	void initTimer();

	const qreal GBcos(int i);
	const qreal GBsin(int i);
	
	qint16 boardHeight();
	qint16 boardWidth();
	
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
	void boardSet();
};
#endif // GAMEBOARD_HPP




