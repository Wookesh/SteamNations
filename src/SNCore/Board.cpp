#include <algorithm>
#include <QSet>
#include <QDebug>
#include <queue>
#include <utility>
#include <qqueue.h>

#include "Board.hpp"
#include "Tile.hpp"
#include "Objects/Town.hpp"

Board::Board(unsigned int width, unsigned int height, unsigned int seed): height_(height), width_(width) 
{
	for (unsigned int i = 0; i < height_; ++i)
		for (unsigned int j = 0; j < width_; ++j)
			tiles_.push_back(new Tile(j, i, Resource::None, qrand() % 5 + 3));
		
	qsrand(seed);
	QSet<Tile *> visited;
	QQueue<Tile *> toVisit;
	for (unsigned int i = 0; i < (height_ * width_ / 100); ++i) {
		Tile *rnd = getTile(qrand() % width_, qrand() % height_);
		switch(i % 3) {
			case 0:
				rnd->setResource(Resource::Gold);
				break;
				
			case 1:
				rnd->setResource(Resource::Research);
				break;
				
			case 2:
				rnd->setResource(Resource::Food);
				break;
				
			default:
				rnd->setResource(Resource::None);
		}
		toVisit.enqueue(rnd);
	}
	
	while (!toVisit.isEmpty()) {
		Tile *tile = toVisit.dequeue();
		
		if (visited.contains(tile))
			continue;
		
		visited.insert(tile);
		unsigned int n = 3;
		QVector<Tile *> neighbours = getNeighbours(tile);
		for (Tile *neighbour : neighbours) {
			if (!visited.contains(neighbour))
				toVisit.enqueue(neighbour);
		}
		
		/* 10% chance that tile is gonna stay empty */
		if (qrand() % 10 == 0 || tile->resource() != Resource::None)
			continue;
		
		unsigned int gold = nOfTilesWith(neighbours, Resource::Gold);
		unsigned int research = nOfTilesWith(neighbours, Resource::Research);
		unsigned int food = nOfTilesWith(neighbours, Resource::Food);
		n = n + gold + research + food;
		unsigned int randomNumber = qrand() % n;
		if (randomNumber < gold + 1)
			tile->setResource(Resource::Gold);
		else if (randomNumber < gold + food + 2)
			tile->setResource(Resource::Food);
		else if (randomNumber < gold + food + research + 3)
			tile->setResource(Resource::Research);
		else 
			qDebug() << "Case not covered";
	}
}

unsigned int Board::height() const
{
	return height_;
}

unsigned int Board::width() const
{
	return width_;
}

unsigned int Board::size() const 
{
	return height_ * width_;
}

unsigned int Board::nOfTilesWith(QVector<Tile *> &tiles, Resource resource) const 
{
	unsigned int amount = 0;
	for (int i = 0; i < tiles.size(); ++i) {
		if (tiles[i]->resource() == resource)
			++amount;
	}
	return amount;
}

Board::~Board() 
{
	qDeleteAll(tiles_);
	tiles_.clear();
}

/*
 * Returns pointer to a tile with (x, y) coordinates in "odd-q" vertical layout
 */
Tile* Board::getTile(int x, int y) const 
{
	if (x < 0 || y < 0 || x >= width_ || y >= height_)
		return nullptr;
	
	return tiles_[x + y * width_];
}

Tile *Board::getTile(QPair<int, int> pos) const
{
	return getTile(pos.first, pos.second);
}

Tile *Board::getTileAxial(QPoint p) const
{
	return getTileAxial(p.x(), p.y());
}


Tile* Board::getTileAxial(int x, int y) const 
{
	int q = x;
	int r = y + (x - (x&1)) / 2;
	
	return getTile(q, r);
}

Tile* Board::getTileCube(int x, int z) const 
{
	int q = x;
	int r = z + (x - (x&1)) / 2;
	
	return getTile(q, r);
}

unsigned int Board::getAbsoluteDistance(const Tile *tile1, const Tile *tile2) const 
{
	QPoint axial1 = tile1->axial();
	QPoint axial2 = tile2->axial();
	
	int q1 = axial1.x();
	int r1 = axial1.y();
	int q2 = axial2.x();
	int r2 = axial2.y();
	
	return (abs(q1 - q2) + abs(r1 - r2) + abs(q1 + r1 - q2 - r2)) / 2;
}

QVector<Tile *> Board::getNeighbours(const Tile *tile) const 
{
	static const QPoint neighbours[] = {
		QPoint(1, 0), QPoint(1, -1), QPoint(0, -1), 
		QPoint(-1, 0), QPoint(-1, 1), QPoint(0, 1)
	};
	
	QVector<Tile *> ret;
	
	for (QPoint neighbour : neighbours) {
		QPoint pos = tile->axial() + neighbour;
		int x = pos.x();
		int y = pos.y();
		
		Tile *tile = getTileAxial(x, y);
		if (tile != nullptr)
			ret.push_back(tile);
	}
	
	return ret;
}

QVector<Tile *> Board::getInRange(const Tile *tile, const int range) const 
{
	QVector<Tile *> inRange;
	QPoint pos = tile->axial();
	int cube_x = pos.x();
	int cube_z = pos.y();
	
	for (int dx = -range; dx <= range; ++dx) {
		for (int dy = std::max(-range, -dx - range); dy <= std::min(range, -dx + range); ++dy) {
			int dz = -dx - dy;
			Tile *reachable = getTileCube(cube_x + dx, cube_z + dz);
			
			if (reachable != nullptr)
				inRange.push_back(reachable);
		}
	}
	
	return inRange;
}

/*
 * Returns a vector of vectors of Tile* pointers. Each index contains vector with tiles
 * that are in range equal to the index.
 * 
 * auto result = getReable(tile_, max_range)
 * result[i] - tiles in range i from tile_
 */
QVector<QVector<Tile *> > Board::getReachable(Tile *tile, const int range, const Player* player) const 
{
	QSet<Tile *> visited;
	visited.insert(tile);
	QVector<QVector<Tile *> > reachable(range + 1);
	reachable[0].push_back(tile);
	
	for (int i = 1; i <= range; ++i) {
		for (auto hex : reachable[i-1]) {
			QVector<Tile *> neighbours = getNeighbours(hex);
			
			for (Tile *neighbour : neighbours) {
				if (!visited.contains(neighbour)) {
					visited.insert(neighbour);
					
					if (!neighbour->passable(player) || !neighbour->visible(player)) {
						continue;
					}
					
					int distance = i + neighbour->weight() - 1;
					if (distance <= range) {
						reachable[distance].push_back(neighbour);
					}
				}
			}
		}
	}
	
	return reachable;
}
/*
 * Priority Queue for path searching. tilePriority are its elements - pairs of 
 * (tile, distance).
 */
typedef std::pair<Tile *, int> tilePriority;

class tileComparison {
	bool reverse;
public:
	tileComparison(const bool& revparam=false) {reverse=revparam;}
	bool operator() (const tilePriority& lhs, const tilePriority& rhs) const {
		if (reverse) return (lhs.second < rhs.second);
		else return (lhs.second > rhs.second);
	}
};

typedef std::priority_queue<tilePriority,std::vector<tilePriority>,tileComparison> tilePQ;

/*
 * Returns path from start to dest. Uses A* with getAbsoluteDistance() function as 
 * its heuristic.
 */
QVector<Tile * > Board::pathToTile(Tile *start, Tile *dest) const 
{
	tilePQ frontier;
	frontier.push(std::make_pair(start, 0));
	
	QMap<Tile *, Tile *> cameFrom;
	QMap<Tile *, int> costSoFar;
	cameFrom[start] = nullptr;
	costSoFar[start] = 0;
	
	while (!frontier.empty()) {
		tilePriority current = frontier.top();
		frontier.pop();
		
		if (current.first == dest)
			break;
		
		for (Tile *next : getNeighbours(current.first)) {
			int newCost = costSoFar[current.first] + next->weight();
			if (!costSoFar.contains(next) || newCost < costSoFar[next]) {
				costSoFar[next] = newCost;
				int priority = newCost + getAbsoluteDistance(next, dest);
				frontier.push(std::make_pair(next, priority));
				cameFrom[next] = current.first;
			}
		}
	}
	
	Tile *current = dest;
	QVector<Tile *> path;
	path.push_front(current);
	while (current != start) {
		current = cameFrom[current];
		path.push_back(current);
	}
	
	return path;
}

/* 
 * Returns tiles that surround the town. If [onlyFree] is true, then only tiles
 * that do not belong to any other town are returned.
 */
QVector<Tile *> Board::getSurroundings(Town *town, bool onlyFree) const 
{
	QVector<Tile *> ret;
	
	Tile *start = town->tile();
	QQueue<Tile *> queue;
	queue.enqueue(start);
	QSet<Tile *> discovered;
	discovered.insert(start);
	
	while (!queue.empty()) {
		Tile *current = queue.dequeue();
		for (Tile *tile : getNeighbours(current)) {
			
			if (!discovered.contains(tile)) {
				
				discovered.insert(tile);
				
				if (tile->localTown() != town) {
					if (tile->town() == nullptr || !onlyFree) {
						ret.push_back(tile);
					}
				} else {
					queue.enqueue(tile);
				}
			}
		}
	}
	
	return ret;
}

QPair<int, int> Board::getUnitSpawnCenter(int number, int total) const
{
	switch (total) {
		case 2: return qMakePair(width_ / 4 * ((number % 2) * 2 + 1), height_ / 2);
		case 3: return qMakePair(width_ / 4 * ((2 * number) % 3 + 1), height_ / 4 * ((number / 2) * 2 + 1));
		case 4: return qMakePair(width_ / 4 * ((number % 2) * 2 + 1), height_ / 4 * ((number / 2) * 2 + 1));
		default: return qMakePair(0, 0);
	}
}

void Board::updateBefore() 
{
	for (Tile *tile : tiles_)
		tile->updateBefore();
}

void Board::addPlayerVisionToTiles(const Player *player) 
{
	for (Tile *tile : tiles_)
		tile->addPlayerToVisionState(player);
}

bool Board::save(QDataStream &out)
{
	out << width_ << height_;
	for (Tile *tile : tiles_)
		tile->save(out);
	return true;
}

bool Board::load(QDataStream &in)
{
	in >> width_ >> height_;
	
	if (width_ < 10 || width_ > 50)
		return false;
	
	if (height_ < 10 || height_ > 50)
		return false;
	
	qDeleteAll(tiles_);
	tiles_.clear();
	
	for (unsigned int i = 0; i < height_; ++i)
		for (unsigned int j = 0; j < width_; ++j)
			tiles_.push_back(new Tile(j, i));
	
	for (Tile *tile : tiles_)
		if (!tile->load(in)) return false;
	
	return true;
}


