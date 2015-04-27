#ifndef SETTLER_HPP
#define SETTLER_HPP

#include "Unit.hpp"

class SettlerPrototype;
class Town;

class Settler : public Unit {
Q_OBJECT
public:
	Settler(Tile *tile, const SettlerPrototype *prototype, Player *owner, QObject *parent = nullptr);
	~Settler();
	
	bool canSettle(const Tile *tile) const;
	bool settle();
	bool canPerform(ActionType action, const Tile *tile) const override;
	Town *createTown();
	
	virtual void updateAfter() override;
	virtual void getAttacked(Soldier *) override;
	int turnWithoutSettle() const;
	
protected:
	virtual ActionType getActionType(Tile *tile) override;
	int turnWithoutSettle_;
signals:
	void townCreated(Player *player);
	void capitalCreated(Player *player);
};

#endif
