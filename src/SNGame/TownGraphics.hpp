#ifndef TOWNRAPHICS_H
#define TOWNRAPHICS_H

#include <QGraphicsRectItem>
#include "../SNCore/SNCommon.hpp"
#include "../SNCore/Town.hpp"

class TownGraphics : public QGraphicsRectItem {

public:
	TownGraphics(Town *town, QGraphicsItem *parent = nullptr);
	~TownGraphics();
	
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	
private:
	Town *town_;
	static const int SIZE = 90;
};

#endif // TILEGRAPHICS _H