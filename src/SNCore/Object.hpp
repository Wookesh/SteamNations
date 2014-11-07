#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QObject>

class Player;
class Tile;

class Object : public QObject {
Q_OBJECT
public:
	Object(Tile *tile, QObject *parent = nullptr);
	virtual ~Object();
	
	Player *owner() const;
	void setOwner(Player *owner);
	
	Tile *tile() const;
	void setTile(Tile *tile);
	
	virtual QString name() const = 0;
	
	virtual void updateBefore() = 0;
	virtual void updateAfter() = 0;
protected:
	Player *owner_;
	Tile *tile_;
signals:
	void ownerChanged();
	void positionChanged();
};

#endif
