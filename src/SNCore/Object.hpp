#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QObject>
#include "SNCommon.hpp"

class Player;
class Tile;

class Object : public QObject {
Q_OBJECT
public:
	enum class Type {
		Town,
		Unit
	};
	
	Object(Tile *tile, SN::ObjectType type, QObject *parent = nullptr);
	virtual ~Object();
	
	Player *owner() const;
	void setOwner(Player *owner);
	
	Tile *tile() const;
	void setTile(Tile *tile);
	
	SN::ObjectType type();
	void setType(SN::ObjectType type);
	
	virtual QString name() const = 0;
	
	virtual void updateBefore() = 0;
	virtual void updateAfter() = 0;
protected:
	Player *owner_;
	Tile *tile_;
	SN::ObjectType type_;
	
signals:
	void ownerChanged();
	void positionChanged();
};

#endif
