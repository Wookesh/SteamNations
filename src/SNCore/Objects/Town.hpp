#ifndef TOWN_HPP
#define TOWN_HPP

#include <QString>

#include "Object.hpp"
#include "../Resources.hpp"
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
	
	void addFood(SNTypes::amount food);
	
	Unit *createUnit(PrototypeType type);
	void getCaptured(Player *player);
	
	void setFoodGoal();
	void addNewTile();
	Tile *chooseBestTile(QVector<Tile *> tiles);
	
	bool canBuild(Tile *tile, Resource building) const;
	void createBuilding(Tile *tile, Resource building);
	
	bool isCapital() const;
	
	SNTypes::population population() const;
	unsigned int size() const;
	
	virtual bool load(QDataStream &in);
	virtual bool save(QDataStream &out);
private:
	QString name_;
	QVector<Tile *> townTiles_;
	SNTypes::population population_;
	SNTypes::amount food_;
	SNTypes::amount foodGoal_;
	bool hasBuiltThisTurn_;
	bool capital_;
	Player *capitalPlayer_;

friend QDataStream &operator<<(QDataStream &out, const Town &town);
friend QDataStream &operator>>(QDataStream &in, Town &town);
};

QDataStream &operator<<(QDataStream &out, const Town &town);
QDataStream &operator>>(QDataStream &in, Town &town);

#endif
