#ifndef TOWNRAPHICS_H
#define TOWNRAPHICS_H

#include <QGraphicsPolygonItem>
#include "../SNCore/SNCommon.hpp"
#include "../SNCore/Town.hpp"

class TownGraphics : public QGraphicsPolygonItem {

public:
	TownGraphics(Town *town);
	~TownGraphics();
	
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	
private:
	Town *town_;
	static const int RADIUS = 80;
};

#endif // TILEGRAPHICS _H
