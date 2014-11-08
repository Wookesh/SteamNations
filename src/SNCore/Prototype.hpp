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
	
	quint8 moveRange() const;
	void setMoveRange(quint8 moveRange);
	
	int cost() const;
	void setCost(int cost);
private:
	QString name_;
	quint8 moveRange_;
	int cost_;
};

#endif
