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
	SNScene(QObject *object);
	~SNScene();
	
	void setBoard(Board *board);
	
	void select(const Tile *tile);
protected:
	
private:
	QMap<const Tile *, TileGraphics *> tileToGraphics_;
	const Object *selectedObject_;
	QList<const SN::Action *> possibleActions_;
	GameManager *game_;
	
	
	void highlightActions();
	
};



#endif