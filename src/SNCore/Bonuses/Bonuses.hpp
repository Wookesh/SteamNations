#ifndef BONUSES_HPP
#define BONUSES_HPP

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
private:
	static BonusManager *instance;
	static QVector<Bonus *> bonuses_;
protected:
	BonusManager();
	virtual ~BonusManager();
};

#endif