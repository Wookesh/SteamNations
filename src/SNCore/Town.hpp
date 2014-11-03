#ifndef TOWN_HPP
#define TOWN_HPP

#include <QString>
#include "Object.hpp"

class Player;
class Tile;
class Prototype;
class Unit;

class Town : public Object {
Q_OBJECT
public:
	Town(QObject *parent = nullptr);
	virtual ~Town();
	
	virtual void updateAfter() override;
	Unit *createUnit(Prototype *);
	void getCaptured(Player *);
private:
	QString name_;
signals:
	void townDestroyed();
};

#endif
