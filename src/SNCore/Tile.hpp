#ifndef TILE_HPP
#define TILE_HPP

#include <QPoint>
#include <QList>
#include <QMap>

#include "Resources.hpp"

class Player;
class Object;
class Town;
class Unit;

EnumClassWithStrings(VisionType, quint8, Invisible, Visible)
EnumClassWithStrings(TileType, quint8, Desert, Field, Forest, Hill, Mountain, Jungle, Random, Ruins1, Ruins2, Snow1, Snow2, Tundra)

class Tile {
public:
	static const QVector<TileType> goldTiles;
	static const QVector<TileType> foodTiles;
	static const QVector<TileType> researchTiles;
	static const QVector<TileType> emptyTiles;
	static const QHash<Resource, QVector<TileType>> tileTypeMap;
	Tile(unsigned int x, unsigned int y, Resource resource = Resource::None, int resourceProduction = 5, unsigned int weight = 1);
	~Tile();
	
	Town *town();
	const Town *town() const;
	void setTown(Town *town);
	
	Town *localTown();
	const Town *localTown() const;
	void setLocalTown(Town *town);
	
	Unit *unit();
	const Unit *unit() const;
	void setUnit(Unit *unit);
	
	Resource resource() const;
	void setResource(Resource resource);
	
	int resourceProduction() const;
	int takeResources();
	void gatherResource(Town *town);
	
	bool passable(const Player *player) const;
	int weight() const;
	
	void updateBefore();
	
	QPoint position() const;
	QPoint axial() const;
	
	Resource building() const;
	void setBuilding(Resource);
	
	QList<const Object *> getObjects() const;
	
	void addPlayerToVisionState(const Player *player);
	QMap <const Player *, VisionType> visionState() const;
	VisionType visionState(const Player *player) const;
	void setVisionState(const Player *player, VisionType visionType);
	bool visible(const Player *player) const;
	
	void setTileType();
	
	TileType tileType() const;
	bool load(QDataStream &in);
	bool save(QDataStream &out);
private:
	Town *town_;
	Town *localTown_;
	Unit *unit_;
	QPoint position_;
	Resource resource_;
	int resourceProduction_;
	int produced_;
	int weight_;
	Resource building_;
	QMap<const Player *, VisionType> visionState_;
	TileType tileType_;
};

#endif
