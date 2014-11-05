#ifndef TILE_HPP
#define TILE_HPP

#include <QPoint>
#include <QList>

class Object;
class Town;
class Unit;

class Tile {
public:
	Tile();
	~Tile();
	
	Town *town();
	void setTown(Town *town);
	
	Unit *unit();
	void setUnit(Unit *unit);
	
	QList<const Object *> getObjects() const;
private:
	Town *town_;
	Unit *unit_;
	QPoint position_;
};

#endif
