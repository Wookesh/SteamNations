#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QMap>
#include <QString>
#include <QVector>


#include "Objects/Prototypes/Prototype.hpp"
#include "Resources.hpp"
#include "Bonuses/Bonuses.hpp"

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
	
	Unit *createUnit(PrototypeType type, Tile *tile);
	void destroyUnit(Unit *unit);
	
	unsigned int resource(Resource resource) const;
	void addResource(Resource resource, unsigned int val);
	bool removeResource(Resource resource, unsigned int val);
	
	Prototype *prototype(PrototypeType type);
	QList<Prototype *> prototypes();
	QList<Prototype *> soldierPrototypes();
	
	Qt::GlobalColor color() const;
	
	bool applyBonus(Bonus *bonus);
	bool hasBonus(BonusType type, SNTypes::tier tier) const;
	
private:
	Town *capital_;
	QString name_;
	QVector<Town *> towns_;
	QVector<Unit *> units_;
	QHash<PrototypeType, Prototype *> prototypes_;
	QHash<PrototypeType, Prototype *> soldierPrototypes_;
	Qt::GlobalColor color_;
	QHash<Resource, unsigned int> resources_;
	QHash<BonusType, QMap<SNTypes::tier, bool> > bonuses;
};

#endif
