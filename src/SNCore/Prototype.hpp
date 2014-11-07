#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

#include <QString>

class Unit;
class Tile;

class Prototype {
public:
	
	enum class Type : qint8 {
		Settler,
		Fighter,
	};
	
	Prototype(const QString &name, int moveRange, int cost);
	virtual ~Prototype();
	
	virtual Unit *createUnit(Tile *tile) = 0;
	
	QString name() const;
	void setName(const QString &name);
	
	int moveRange() const;
	void setMoveRange(int moveRange);
	
	int cost() const;
	void setCost(int cost);
private:
	QString name_;
	int moveRange_;
	int cost_;
};

#endif
