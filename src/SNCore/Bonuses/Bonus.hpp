#ifndef BONUS_HPP
#define BONUS_HPP

#include <QtGlobal>
#include <QHash>

#include "../EnumHelpers.hpp"
#include "../Resources.hpp"
#include "SNTypes.hpp"

class Player;

EnumClassWithStrings(BonusType, quint8, War, Def, Eco)

static const QHash<SNTypes::tier, SNTypes::amount> bonusCost = {
	{1, 50},
	{2, 100},
	{3, 200},
};

class Bonus {
public:
	Bonus(SNTypes::tier tier, BonusType type);
	~Bonus();
	
	virtual bool apply(Player *player) = 0;
	SNTypes::amount cost() const;
	SNTypes::tier tier() const;
	BonusType type() const;
protected:
	SNTypes::tier tier_;
	BonusType type_;
	
	bool canApply(Player *player) const;
};


#endif