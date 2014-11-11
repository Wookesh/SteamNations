#ifndef SNSCENE_HPP
#define SNSCENE_HPP

#include <QGraphicsScene>
#include <QMap>
#include "../SNCore/Board.hpp"
#include "../SNCore/GameManager.hpp"

class Settler;
class Soldier;
class Unit;
class TileGraphics;
class UnitGraphics;

class SNScene : public QGraphicsScene {
Q_OBJECT
public:
	SNScene(GameManager *gameManager, QObject *parent = nullptr);
	~SNScene();
	
	void setBoard(Board *board);
	
	void select(const Tile *tile);
	const Object *selectedObject() const;
	const QVector<Action *> &objectActions() const;
protected:
	
private:
	QMap<const Tile *, TileGraphics *> tileToItem_;
	QMap<const Unit *, UnitGraphics *> unitToItem_;
	const Object *selectedObject_;
	QVector<Action *> possibleActions_;
	GameManager *gameManager_;
	
	void highlightActions();
	void connectUnit(const Unit *unit, UnitGraphics *unitG);
	void createTown(const Town *town);
	void createSettler(const Settler *settler);
	void createSoldier(const Soldier *soldier);
	void createTile(const Tile *tile);
	void createBoard();
	void clearHighlight();
private slots:
	void createObject(UID id);
signals:
	void selected();
};



#endif