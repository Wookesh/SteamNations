#ifndef TILE_HPP
#define TILE_HPP

#include <QPoint>
#include <QList>

#include "Resources.hpp"

class Object;
class Town;
class Unit;

class Tile {
public:
	Tile(unsigned int x, unsigned int y, Resource resource = Resource::None, int resourceProduction = 5);
	~Tile();
	
	Town *town();
	const Town *town() const;
	void setTown(Town *town);
	
	Unit *unit();
	const Unit *unit() const;
	void setUnit(Unit *unit);
	
	Resource resource() const;
	
	int resourceProduction() const;
	int takeResources();
	
	void updateBefore();
	
	QPoint position() const;
	QPoint axial() const;
	
	QList<const Object *> getObjects() const;
private:
	Town *town_;
	Unit *unit_;
	QPoint position_;
	Resource resource_;
	int resourceProduction_;
	int produced_;
};

#endif
