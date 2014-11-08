#ifndef TILEGRAPHICS_H
#define TILEGRAPHICS_H

#include <QGraphicsPolygonItem>
#include "../SNCore/Tile.hpp"
#include "../SNCore/Action.hpp"

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
	Action::Type actionType_;
	
	void highlight(Action::Type actionType);
	
	static QPolygonF &hexagon();
	static QColor highlightColor(Action::Type type);
	static constexpr qreal OPACITY = 0.2;
};

#endif // TILEGRAPHICS _H