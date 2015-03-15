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
protected:
	Player *owner_;
	Tile *tile_;
	ObjectType type_;
	UID id_;
	
signals:
	void ownerChanged(Player *player);
	void positionChanged();
	void objectDestroyed(UID id);
friend QDataStream &operator<<(QDataStream &out, const Object &object);
friend QDataStream &operator>>(QDataStream &in, Object &object);
};

QDataStream &operator<<(QDataStream &out, const Object &object);
QDataStream &operator>>(QDataStream &in, Object &object);


#endif
