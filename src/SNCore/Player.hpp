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
	Player(const QString &name, Qt::GlobalColor color);
	virtual ~Player();
	
	QString name() const;
	
	void updateBefore();
	void updateAfter();
	
	void obtainTown(Town *town);
	void destroyTown(Town *town);
	unsigned int getTownCount();
	
	Town *capital();
	void setCapital(Town *town);
	
	Unit *createUnit(ProtoType type, Tile *tile);
	void destroyUnit(Unit *unit);
	
	Prototype *prototype(ProtoType type);

	Qt::GlobalColor color() const;
private:
	Town *capital_;
	QString name_;
	QVector<Town *> towns_;
	QVector<Unit *> units_;
	QHash<ProtoType, Prototype *> prototypes_;
	Qt::GlobalColor color_;
};

#endif
