#ifndef SOLDIERPROTOTYPE_HPP
#define SOLDIERPROTOTYPE_HPP

#include "Prototype.hpp"

#include <QMap>

class SoldierPrototype : public Prototype {
public:
	static const QHash<PrototypeType, unsigned int> ACTION_POINTS;
	static const QHash<PrototypeType, unsigned int> BASE_COST;
	static const QHash<PrototypeType, QString> BASE_NAME;

	SoldierPrototype(PrototypeType type, const QString &name, int moveRange, int cost);
	SoldierPrototype(PrototypeType type);
	~SoldierPrototype();
	
	virtual Unit *createUnit(Tile *tile, Player *owner) override;
	
};

#endif
