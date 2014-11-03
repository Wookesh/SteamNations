#ifndef BOARD_HPP
#define BOARD_HPP

#include <QVector>
#include "Tile.hpp"

class Board {
public:
	Board();
	~Board();
private:
	QVector<QVector<Tile>> tiles_;
};

#endif
