#ifndef BOARDFIELD_HPP
#define BOARDFIELD_HPP

#include <QSGNode>
#include <QColor>

class Unit;
class Town;
class ActionType;
class Tile;

class BoardField {

public:
	BoardField(QSGNode *node, Tile *tile);
	
	QSGNode *node();
	
	const Unit *unit();
	void setUnit( Unit *unit);
	
	const Town *town();
	void setTown( Town *town);
	
	void highlight(ActionType actionType);
	void unhighlight();
	
	QColor highlightColor(ActionType type);
	QColor tileColor();
		
private:
	QSGNode *node_;
	Unit *unit_;
	Town *town_;
	Tile *tile_;
	bool highlighted_;
	
	
	
	
};


#endif //BOARDFIELD_HPP