#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

#include <QString>
#include "../../EnumHelpers.hpp"

class Player;
class Unit;
class Tile;

EnumClassWithStrings(PrototypeType, quint8, Settler, Infantry, Heavy, Artillery)

class Prototype {
public:
	
	Prototype(PrototypeType type, const QString &name, int moveRange, int cost);
	virtual ~Prototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) = 0;
	
	PrototypeType type() const;
	
	QString name() const;
	void setName(const QString &name);
	
	quint8 moveRange() const;
	void setMoveRange(quint8 moveRange);
	
	unsigned int cost() const;
	void setCost(int cost);
	
protected:
	PrototypeType type_;
	QString name_;
	quint8 moveRange_;
	unsigned int cost_;
};

#endif
