#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

#include <QString>
#include "../../EnumHelpers.hpp"

class Player;
class Unit;
class Tile;

EnumClassWithStrings(ProtoType, quint8, Settler, Soldier)

class Prototype {
public:
	
	Prototype(ProtoType type, const QString &name, int moveRange, int cost);
	virtual ~Prototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) = 0;
	
	ProtoType type() const;
	
	QString name() const;
	void setName(const QString &name);
	
	quint8 moveRange() const;
	void setMoveRange(quint8 moveRange);
	
	int cost() const;
	void setCost(int cost);
	
protected:
	ProtoType type_;
	QString name_;
	quint8 moveRange_;
	int cost_;
};

#endif
