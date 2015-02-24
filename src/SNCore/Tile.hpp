#ifndef TILE_HPP
#define TILE_HPP

#include <QPoint>
#include <QList>

#include "Resources.hpp"

class Player;
class Object;
class Town;
class Unit;

class Tile {
public:
	Tile(unsigned int x, unsigned int y, Resource resource = Resource::None, int resourceProduction = 5, unsigned int weight = 1);
	~Tile();
	
	Town *town();
	const Town *town() const;
	void setTown(Town *town);
	
	Town *localTown();
	const Town *localTown() const;
	void setLocalTown(Town *town);
	
	Unit *unit();
	const Unit *unit() const;
	void setUnit(Unit *unit);
	
	Resource resource() const;
	void setResource(Resource resource);
	
	int resourceProduction() const;
	int takeResources();
	void gatherResource(Town *town);
	
	bool passable(const Player *player) const;
	int weight() const;
	
	void updateBefore();
	
	QPoint position() const;
	QPoint axial() const;
	
	QList<const Object *> getObjects() const;
private:
	Town *town_;
	Town *localTown_;
	Unit *unit_;
	QPoint position_;
	Resource resource_;
	int resourceProduction_;
	int produced_;
	int weight_;
};

#endif
