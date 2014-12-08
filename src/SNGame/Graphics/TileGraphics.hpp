#ifndef TILEGRAPHICS_H
#define TILEGRAPHICS_H

#include <QGraphicsPolygonItem>
#include "../../SNCore/Tile.hpp"
#include "../../SNCore/Actions/Action.hpp"

class TileGraphics : public QGraphicsPolygonItem {
public:
	TileGraphics(const Tile *tile, QGraphicsItem *parent = nullptr);
	~TileGraphics();
	
	void highlight(ActionType actionType);
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
	
private:
	const Tile *tile_;
	static const int RADIUS = 80;
	bool pressed_;
	ActionType actionType_;
	
	static const QPolygonF &hexagon();
	static QColor highlightColor(ActionType type);
	static QColor tileColor(Resource resource);
	static constexpr qreal OPACITY = 0.5;
};

#endif // TILEGRAPHICS _H