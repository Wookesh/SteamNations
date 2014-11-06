#ifndef SNGRAPHICS_HPP
#define SNGRAPHICS_HPP
#include <QPoint>

inline QPointF coordToPos(int x, int y) 
{
	return QPointF(x * 120, y * 80 * sqrt(3) + (x % 2 == 0 ? 0 : 40 * sqrt(3)));
}

inline QPointF coordToPos(QPoint coord)
{
	return coordToPos(coord.x(), coord.y());
}



#endif