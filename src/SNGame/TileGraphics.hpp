#ifndef TILEGRAPHICS_H
#define TILEGRAPHICS_H

#include <QGraphicsPolygonItem>
#include "../SNCore/SNCommon.hpp"
#include "../SNCore/Tile.hpp"

class TileGraphics : public QGraphicsPolygonItem {

public:
	TileGraphics(const Tile *tile, QGraphicsItem *parent = nullptr);
	~TileGraphics();
	
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	
private:
	const Tile *tile_;
	static const int RADIUS = 80;
	bool pressed_;
	
	void highlight(SN::Action action);
	
	static QPolygonF &hexagon();
};

#endif // TILEGRAPHICS _H