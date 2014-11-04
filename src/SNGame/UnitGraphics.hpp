#ifndef UNITGRAPHICS_H
#define UNITGRAPHICS_H

#include <QGraphicsPolygonItem>
#include "../SNCore/SNCommon.hpp"
#include "../SNCore/Unit.hpp"

class UnitGraphics : public QGraphicsPolygonItem {

public:
	UnitGraphics(Unit *unit);
	~UnitGraphics();
	
protected:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	
private:
	Unit *unit_;
	static const int RADIUS = 80;
	void animate(SN::Action action);
};

#endif // TILEGRAPHICS _H
