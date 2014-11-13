#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QMap>
#include <QString>
#include <QVector>

#include "Objects/Prototypes/Prototype.hpp"
#include "Tile.hpp"

class Tile;
class Town;
class Unit;

class Player {
public:
	Player(const QString &name);
	virtual ~Player();
	
	QString name() const;
	
	void updateBefore();
	void updateAfter();
	
	void obtainTown(Town *town);
	void destroyTown(Town *town);
	
	Town *capital();
	void setCapital(Town *town);
	
	Unit *createUnit(Prototype::Type type, Tile *tile);
	void destroyUnit(Unit *unit);
	
	Prototype *prototype(Prototype::Type type);
private:
	Town *capital_;
	QString name_;
	QVector<Town *> towns_;
	QVector<Unit *> units_;
	QMap<Prototype::Type, Prototype *> prototypes_;
};

#endif
