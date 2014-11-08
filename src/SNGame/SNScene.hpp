#ifndef SNSCENE_HPP
#define SNSCENE_HPP

#include <QGraphicsScene>
#include <QMap>
#include "../SNCore/Board.hpp"
#include "../SNCore/GameManager.hpp"
#include "TileGraphics.hpp"

class SNScene : public QGraphicsScene {
Q_OBJECT
public:
	SNScene(GameManager *gameManager, QObject *parent = nullptr);
	~SNScene();
	
	void setBoard(Board *board);
	
	void select(const Tile *tile);
	const Object *selectedObject();
protected:
	
private:
	QMap<const Tile *, TileGraphics *> tileToGraphics_;
	const Object *selectedObject_;
	QList<const Action *> possibleActions_;
	GameManager *gameManager_;
	
	void highlightActions();
signals:
	void selectedTown();
	void selectedUnit();
};



#endif