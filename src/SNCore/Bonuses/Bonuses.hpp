#ifndef BONUSES_HPP
#define BONUSES_HPP

#include <QPair>

#include "Bonus.hpp"
#include "WarfareBonuses.hpp"
#include "DefenseBonuses.hpp"
#include "EconomyBonuses.hpp"
#include <QString>

class BonusManager : public QObject {
Q_OBJECT
public:	
	Q_INVOKABLE void tryToApplyBonus(int bonus);
	Q_INVOKABLE bool isApplied(int bonus);
	Q_INVOKABLE bool isAffordable(int bonus);
	Q_INVOKABLE QString desc(int bonus);
	static BonusManager *get();
	static void init();
	static void clean();
	void reloadBonuses();
	Bonus *getBonus(BonusType type, SNTypes::tier tier);
	SNTypes::amount cost(SNTypes::tier tier);
	QList< QPair<BonusType, SNTypes::tier> > applicableBonuses(Player *player);
	QList< QPair<BonusType, SNTypes::tier> > appliedBonuses(Player *player);
	bool canApply(Player *, BonusType, SNTypes::tier);
	void applyBonus(Player *, BonusType, SNTypes::tier);
	
signals:
	void bonusesUpdated();
private:
	static BonusManager *instance;
	static QVector<Bonus *> bonuses_;
protected:
	BonusManager();
	virtual ~BonusManager();
};

#endif