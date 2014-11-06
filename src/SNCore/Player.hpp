#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QString>
#include <QList>
#include <QMap>

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
	Prototype *prototype(Prototype::Type type);
private:
	QString name_;
	QList<Town *> towns_;
	QList<Unit *> units_;
	QMap<Prototype::Type, Prototype *> prototypes_;
};

#endif
