#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QMap>
#include <QString>
#include <QVector>

#include "Prototype.hpp"

class Town;
class Unit;

class Player {
public:
	Player(const QString &name);
	virtual ~Player();
	
	QString name() const;
	
	void updateBefore();
	void updateAfter();
	
	Unit *createUnit(Prototype::Type type);
	Prototype *prototype(Prototype::Type type);
private:
	QString name_;
	QVector<Town *> towns_;
	QVector<Unit *> units_;
	QMap<Prototype::Type, Prototype *> prototypes_;
};

#endif
