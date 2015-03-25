#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QMap>
#include <QString>
#include <QVector>
#include <QtGui/QColor>


#include "Objects/Prototypes/Prototype.hpp"
#include "Resources.hpp"
#include "Bonuses/Bonuses.hpp"

class Tile;
class Town;
class Unit;

class Player {
public:
	static const QHash<Resource, SNTypes::amount> BASE_BUILDING_COST;
	
	Player(const QString &name, QColor color);
	virtual ~Player();
	
	QString name() const;
	QColor color() const;
	
	void updateBefore();
	void updateAfter();
	
	void obtainTown(Town *town);
	void destroyTown(Town *town);
	unsigned int getTownCount();
	
	Town *capital();
	void setCapital(Town *town);
	int nOfTowns();
	
	Unit *createUnit(PrototypeType type, Tile *tile);
	void destroyUnit(Unit *unit);
	unsigned int getUnitsCount();
	
	unsigned int resource(Resource resource) const;
	void addResource(Resource resource, unsigned int val);
	bool removeResource(Resource resource, unsigned int val);
	
	Prototype *prototype(PrototypeType type);
	QList<Prototype *> prototypes();
	QList<Prototype *> soldierPrototypes();
	
	bool applyBonus(Bonus *bonus);
	bool hasBonus(BonusType type, SNTypes::tier tier) const;
	
	bool canAffordBuilding(Resource type);
	void payForBuilding(Resource type);
	
	SNTypes::population population() const;
	unsigned int landSize() const;
	
	SNTypes::amount lastIncome(Resource resource) const;
	
	bool load(QDataStream &in);
	bool save(QDataStream &out);
	
private:
	Town *capital_;
	QString name_;
	QColor color_;
	QVector<Town *> towns_;
	QVector<Unit *> units_;
	QHash<PrototypeType, Prototype *> prototypes_;
	QHash<PrototypeType, Prototype *> soldierPrototypes_;
	QHash<Resource, unsigned int> resources_;
	QHash<BonusType, QMap<SNTypes::tier, bool> > bonuses_;
	QHash<Resource, SNTypes::amount> buildingCost_;
	QHash<Resource, SNTypes::amount> lastIncome_;
};

#endif
