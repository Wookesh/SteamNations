#ifndef TILEGRAPHICS_H
#define TILEGRAPHICS_H

#include <QGraphicsPolygonItem>
#include "../SNCore/SNCommon.hpp"
#include "../SNCore/Tile.hpp"

class TileGraphics : public QGraphicsPolygonItem {

public:
	TileGraphics(Tile *tile);
	~TileGraphics();
	
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	
private:
	Tile *tile_;
	static const int RADIUS = 80;
	bool pressed_;
	
	void highlight(SN::Action action);
};

#endif // TILEGRAPHICS _H
