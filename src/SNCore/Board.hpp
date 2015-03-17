#ifndef BOARD_HPP
#define BOARD_HPP

#include <QVector>
#include "Resources.hpp"
#include <QPoint>
#include "SNTypes.hpp"
#include "Objects/Prototypes/Prototype.hpp"

class Player;
class Tile;
class Town;

class Board {
public:
	typedef QVector<const Tile *>::const_iterator const_iterator;
	const_iterator begin() const { return tiles_.constBegin(); };
	const_iterator end() const { return tiles_.constEnd(); };
	
	static const int MAXHEIGHT = 50;
	static const int MAXWIDTH = 50;
	Board(unsigned int width, unsigned int height, unsigned int seed = qrand());
	~Board();
	
	Tile *getTile(int x, int y) const;
	Tile *getTile(QPair<int, int > pos) const;
	Tile *getTileAxial(QPoint p) const;
	Tile *getTileAxial(int x, int y) const;
	Tile *getTileCube(int x, int y, int z) const;
	
	unsigned int nOfTilesWith(QVector<Tile *> &tiles, Resource resource) const;
	unsigned int getAbsoluteDistance(const Tile *tile1, const Tile *tile2) const;
	
	QVector<Tile *> getNeighbours(const Tile *tile) const;
	QVector<Tile *> getInRange(const Tile *tile, const int range) const;
	QVector<QVector<Tile *> > getReachable(Tile *tile, const int range, const Player *player) const;
	QVector<Tile *> pathToTile(Tile *start, Tile *dest) const;
	QVector<Tile *> getSurroundings(Town *town, bool onlyFree=0) const;
	
	QPair<int, int> getUnitSpawnCenter(int number, int total) const;
	
	unsigned int width();
	unsigned int height();
	
	void updateBefore();
	
	void addPlayerVisionToTiles(const Player *player);
private:
	unsigned int height_;
	unsigned int width_;
	QVector<Tile *> tiles_;
};

#endif