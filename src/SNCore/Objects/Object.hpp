#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QObject>
#include "../Serial.hpp"
#include "../EnumHelpers.hpp"

class Player;
class Tile;

EnumClassWithStrings(ObjectType, quint8, Unit, Town)


class Object : public QObject {
Q_OBJECT
public:
	
	Object(Tile *tile, ObjectType type, Player *owner, QObject *parent = nullptr);
	virtual ~Object();
	
	Player *owner();
	const Player *owner() const;
	void setOwner(Player *owner);
	
	Tile *tile();
	const Tile *tile() const;
	void setTile(Tile *tile);
	
	ObjectType type() const;
	void setType(ObjectType type);
	
	virtual QString name() const = 0;
	
	UID id() const;
	void setId(const UID); 
	
	virtual void updateBefore() = 0;
	virtual void updateAfter() = 0;
	
	virtual bool load(QDataStream &in) = 0;
	virtual bool save(QDataStream &out) = 0;
protected:
	Player *owner_;
	Tile *tile_;
	ObjectType type_;
	UID id_;
	
signals:
	void ownerChanged(Player *player);
	void positionChanged();
	void objectDestroyed(UID id);
};


#endif
