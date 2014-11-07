#ifndef UNITGRAPHICS_H
#define UNITGRAPHICS_H


#include <QGraphicsRectItem>
#include "../SNCore/SNCommon.hpp"
#include "../SNCore/Unit.hpp"

class UnitGraphics : public QGraphicsRectItem {

public:
	UnitGraphics(const Unit *unit, QGraphicsItem *parent = nullptr);
	~UnitGraphics();
	
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	
private:
	const Unit *unit_;
	static const int SIZE = 80;
	void animate(SN::Action action);
};

#endif // TILEGRAPHICS _H