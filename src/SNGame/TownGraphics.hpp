#ifndef TOWNRAPHICS_H
#define TOWNRAPHICS_H

#include <QGraphicsRectItem>
#include "../SNCore/Town.hpp"

class TownGraphics : public QGraphicsRectItem {
public:
	TownGraphics(const Town *town, QGraphicsItem *parent = nullptr);
	~TownGraphics();
	
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	
private:
	const Town *town_;
	static const int SIZE = 90;
};

#endif