#ifndef UNITGRAPHICS_H
#define UNITGRAPHICS_H


#include <QGraphicsRectItem>
#include "../../SNCore/Objects/Unit.hpp"
#include "../../SNCore/Actions/Action.hpp"

class UnitGraphics : public QGraphicsRectItem {
public:
	UnitGraphics(const Unit *unit, QGraphicsItem *parent = nullptr);
	~UnitGraphics();
	
	void updatePosition();
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
private:
	const Unit *unit_;
	static const int SIZE = 80;
	void animate(Action *action);
};

#endif // TILEGRAPHICS _H