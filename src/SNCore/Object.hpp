#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QObject>

class Player;
class Tile;

class Object : public QObject {
Q_OBJECT
public:
	enum class Type {
		Town,
		Unit
	};
	
	Object(Tile *tile, Type type, QObject *parent = nullptr);
	virtual ~Object();
	
	Player *owner();
	const Player *owner() const;
	void setOwner(Player *owner);
	
	Tile *tile();
	const Tile *tile() const;
	void setTile(Tile *tile);
	
	Type type();
	void setType(Type type);
	
	virtual QString name() const = 0;
	
	virtual void updateBefore() = 0;
	virtual void updateAfter() = 0;
protected:
	Player *owner_;
	Tile *tile_;
	Type type_;
	
signals:
	void ownerChanged();
	void positionChanged();
};

#endif
