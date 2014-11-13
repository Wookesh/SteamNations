#include <algorithm>

#include "Board.hpp"
#include "Objects/Settler.hpp"
#include "Objects/Prototypes/SettlerPrototype.hpp"

Board::Board(unsigned int width, unsigned int height): height_(height), width_(width) {
    for (unsigned int i = 0; i < height_; ++i)
		for (unsigned int j = 0; j < width_; ++j) {
			Tile *tile = new Tile(j, i);
			tiles_.push_back(tile);
		}
}

Board::~Board() {
	qDeleteAll(tiles_);
}

/*
 * Returns pointer to a tile with (x, y) coordinates in "odd-q" vertical layout
 */
Tile* Board::getTile(int x, int y) const {
	if (x < 0 || y < 0 || x + y * width_ >= height_ * width_)
		return nullptr;
	
	return tiles_[x + y * width_];
}

Tile* Board::getTileAxial(int x, int y) const {
	int q = x;
	int r = y + (x - (x&1)) / 2;
	
	return getTile(q, r);
}

Tile* Board::getTileCube(int x, int y, int z) const {
	int q = x;
	int r = z + (x - (x&1)) / 2;
	
	return getTile(q, r);
}

unsigned int Board::getAbsoluteDistance(const Tile *tile1, const Tile *tile2) const {
	QPoint axial1 = tile1->axial();
	QPoint axial2 = tile2->axial();
	
	int q1 = axial1.x();
	int r1 = axial1.y();
	int q2 = axial2.x();
	int r2 = axial2.y();
	
	return (abs(q1 - q2) + abs(r1 - r2) + abs(q1 + r1 - q2 - r2)) / 2;
}

QVector<Tile *> Board::getNeighbours(const Tile *tile) const {
	static const QPoint neighbours[] = {
		QPoint(1, 0), QPoint(1, -1), QPoint(0, -1), 
		QPoint(-1, 0), QPoint(-1, 1), QPoint(0, 1)
	};
	
	QVector<Tile *> ret;
	
	for (QPoint neighbour : neighbours) {
		QPoint pos = tile->position() + neighbour;
		int x = pos.x();
		int y = pos.y();
		
		Tile *tile = getTile(x, y);
		if (tile != nullptr)
			ret.push_back(tile);
	}
	
	return ret;
}

QVector<Tile *> Board::getInRange(const Tile *tile, const int range) const {
	QVector<Tile *> inRange;
	QPoint pos = tile->axial();
	int cube_x = pos.x();
	int cube_z = pos.y();
	int cube_y = -cube_x - cube_z;
	
	for (int dx = -range; dx <= range; ++dx) {
		for (int dy = std::max(-range, -dx - range); dy <= std::min(range, -dx + range); ++dy) {
			int dz = -dx - dy;
			Tile *reachable = getTileCube(cube_x + dx, cube_y + dy, cube_z + dz);
			
			if (reachable != nullptr)
				inRange.push_back(reachable);
		}
	}
	
	return inRange;
}
