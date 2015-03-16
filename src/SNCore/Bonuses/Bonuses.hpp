#ifndef BONUSES_HPP
#define BONUSES_HPP

#include <QPair>

#include "Bonus.hpp"
#include "WarfareBonuses.hpp"
#include "DefenseBonuses.hpp"
#include "EconomyBonuses.hpp"

class BonusManager {
public:	
	static BonusManager *get();
	static void init();
	static void clean();
	Bonus *getBonus(BonusType type, SNTypes::tier tier);
	SNTypes::amount cost(SNTypes::tier tier);
	QList< QPair<BonusType, SNTypes::tier> > applicableBonuses(Player *player);
	QList< QPair<BonusType, SNTypes::tier> > appliedBonuses(Player *player);
	bool canApply(Player *, BonusType, SNTypes::tier);
	void applyBonus(Player *, BonusType, SNTypes::tier);
private:
	static BonusManager *instance;
	static QVector<Bonus *> bonuses_;
protected:
	BonusManager();
	virtual ~BonusManager();
};

#endif