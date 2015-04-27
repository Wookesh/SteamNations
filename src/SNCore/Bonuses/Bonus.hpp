#ifndef BONUS_HPP
#define BONUS_HPP

#include <QtGlobal>
#include <QHash>

#include "../Config.hpp"
#include "../EnumHelpers.hpp"
#include "../Resources.hpp"
#include "../SNTypes.hpp"

class Player;

EnumClassWithStrings(BonusType, quint8, War, Def, Eco)

static const QHash<SNTypes::tier, SNTypes::amount> bonusCost = {
	{1, SNCfg::TECHNOLOGY_COST_TIER1},
	{2, SNCfg::TECHNOLOGY_COST_TIER2},
	{3, SNCfg::TECHNOLOGY_COST_TIER3},
};

class Bonus {
public:
	Bonus(SNTypes::tier tier, BonusType type);
	virtual ~Bonus();
	
	virtual bool apply(Player *player) = 0;
	
	SNTypes::amount cost() const;
	SNTypes::tier tier() const;
	BonusType type() const;
	bool canApply(Player *player) const;
protected:
	SNTypes::tier tier_;
	BonusType type_;
};


#endif