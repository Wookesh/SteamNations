#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

#include <QString>
#include "../../EnumHelpers.hpp"
#include "../../SNTypes.hpp"


class Player;
class Unit;
class Tile;

EnumClassWithStrings(PrototypeType, quint8, Settler, Infantry, Heavy, Artillery)

class Prototype {
public:
	
	Prototype(PrototypeType type, const QString &name, SNTypes::ap actionPoints, SNTypes::amount cost, SNTypes::hp health, SNTypes::distance visionRange);
	virtual ~Prototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) = 0;
	
	PrototypeType type() const;
	
	const QString &name() const;
	void setName(const QString &name);
	
	SNTypes::ap actionPoints() const;
	void setActionPoints(SNTypes::ap actionPoints);
	
	SNTypes::amount cost() const;
	void setCost(SNTypes::amount cost);
	
	SNTypes::hp health() const;
	void setHealth(SNTypes::hp health);
	
	SNTypes::distance visionRange() const;
	void setVisionRange(SNTypes::distance visionRange);
	
	void addHealthBonus(float bonus);
	void setHealthBonus(float bonus);
	
	virtual bool load(QDataStream &in);
	virtual bool save(QDataStream &out);
	
protected:
	PrototypeType type_;
	QString name_;
	SNTypes::ap actionPoints_;
	SNTypes::amount cost_;
	SNTypes::hp health_;
	float healthBonus_;
	SNTypes::distance visionRange_;
};

#endif
