#ifndef TILEGRAPHICS_H
#define TILEGRAPHICS_H

#include <QGraphicsPolygonItem>
#include "../../SNCore/Tile.hpp"
#include "../../SNCore/Actions/Action.hpp"

class TileGraphics : public QGraphicsPolygonItem {
public:
	TileGraphics(const Tile *tile, QGraphicsItem *parent = nullptr);
	~TileGraphics();
	
	void highlight(Action::Type actionType);
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
	
private:
	const Tile *tile_;
	static const int RADIUS = 80;
	bool pressed_;
	Action::Type actionType_;
	
	static const QPolygonF &hexagon();
	static QColor highlightColor(Action::Type type);
	static constexpr qreal OPACITY = 0.2;
};

#endif // TILEGRAPHICS _H