#ifndef TILE_HPP
#define TILE_HPP

#include <QPoint>

class Object;
class Town;
class Unit;

class Tile {
public:
	Tile();
	~Tile();
	
	void reactWith(Object *object);
	
	Town *town() const;
	void setTown(Town *town);
	
	Unit *unit() const;
	void setUnit(Unit *unit);
private:
	Town *town_;
	Unit *unit_;
	QPoint position_;
};

#endif
