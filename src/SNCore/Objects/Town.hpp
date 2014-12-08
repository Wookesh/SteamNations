#ifndef TOWN_HPP
#define TOWN_HPP

#include <QString>

#include "Object.hpp"
#include "Prototypes/Prototype.hpp"

class Player;
class Tile;
class Prototype;
class Unit;
class GameManager;

class Town : public Object {
Q_OBJECT
public:
	Town(Tile *tile, Player *owner, const QString &name = tr("Town"), QObject *parent = nullptr);
	virtual ~Town();
	
	virtual void updateBefore() override;
	virtual void updateAfter() override;
	
	virtual QString name() const override;
	
	bool canRecruit(PrototypeType type);
	
	Unit *createUnit(PrototypeType type);
	void getCaptured(Player *player);
private:
	QString name_;
	QVector<Tile *> townTiles_;
};

#endif
