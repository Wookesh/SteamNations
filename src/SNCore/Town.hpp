#ifndef TOWN_HPP
#define TOWN_HPP

#include <QString>

#include "Object.hpp"
#include "Prototype.hpp"

class Player;
class Tile;
class Prototype;
class Unit;

class Town : public Object {
Q_OBJECT
public:
	Town(Tile *tile, const QString &name = tr("Town"), QObject *parent = nullptr);
	virtual ~Town();
	
	virtual void updateBefore() override;
	virtual void updateAfter() override;
	
	virtual QString name() const override;
	
	Unit *createUnit(Prototype::Type type);
	void getCaptured(Player *player);
private:
	QString name_;
	Player *owner_;
signals:
	void townDestroyed();
};

#endif
