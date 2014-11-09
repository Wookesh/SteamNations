#ifndef TILE_HPP
#define TILE_HPP

#include <QPoint>
#include <QList>

class Object;
class Town;
class Unit;

class Tile {
public:
	Tile(unsigned int x, unsigned int y);
	~Tile();
	
	Town *town();
	const Town *town() const;
	void setTown(Town *town);
	
	Unit *unit();
	const Unit *unit() const;
	void setUnit(Unit *unit);
	
	QPoint position() const;
	QPoint axial() const;
	
	QList<const Object *> getObjects() const;
private:
	Town *town_;
	Unit *unit_;
	QPoint position_;
};

#endif
