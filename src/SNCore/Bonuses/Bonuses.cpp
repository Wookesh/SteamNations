#include "Bonuses.hpp"
#include "GameManager.hpp"
#include "Player.hpp"

QVector<Bonus *> BonusManager::bonuses_ = QVector<Bonus *>(9);

BonusManager *BonusManager::instance = nullptr;

BonusManager *BonusManager::get() {
	if (instance == nullptr) {
		init();
	}

	return instance;
}

void BonusManager::init() {
	clean();
	instance = new BonusManager();
}

void BonusManager::clean() {
	if (instance != nullptr) {
		BonusManager *aux = instance;
		instance = nullptr;
		delete aux;
	}
}

BonusManager::BonusManager() {
	// DefenseBonuses
	bonuses_[0] = new DefenseT1Bonus();
	bonuses_[1] = new DefenseT2Bonus();
	bonuses_[2] = new DefenseT3Bonus();

	// WarfareBonuses
	bonuses_[3] = new WarfareT1Bonus();
	bonuses_[4] = new WarfareT2Bonus();
	bonuses_[5] = new WarfareT3Bonus();

	// EconomyBonuses
	bonuses_[6] = new EconomyT1Bonus();
	bonuses_[7] = new EconomyT2Bonus();
	bonuses_[8] = new EconomyT3Bonus();
}

BonusManager::~BonusManager() {
	for (int i = 0; i < 9; ++i)
		delete (bonuses_[i]);
}


Bonus *BonusManager::getBonus(BonusType type, SNTypes::tier tier) {
	int aux;
	
	if (type == BonusType::Def)
		aux = 0;
	else if (type == BonusType::War)
		aux = 1;
	else if (type == BonusType::Eco)
		aux = 2;
	else
		return nullptr;
		
	if (tier > 3 || tier <= 0)
		return nullptr;
	
	return bonuses_[aux * 3 + tier - 1];
}

SNTypes::amount BonusManager::cost (SNTypes::tier tier) {
	return bonusCost[tier];
}

QList< QPair< BonusType, SNTypes::tier > > BonusManager::applicableBonuses(Player *player) {
	QList< QPair< BonusType, SNTypes::tier > > ret;
	
	
	for (Bonus *bonus : bonuses_) {
		if (bonus->canApply(player)) {
			ret.append(qMakePair<BonusType, SNTypes::tier>(bonus->type(), bonus->tier()));
		}
	}
	
	return ret;
}

QList< QPair< BonusType, SNTypes::tier > > BonusManager::appliedBonuses(Player *player) {
	QList< QPair< BonusType, SNTypes::tier > > ret;
	
	for (Bonus *bonus : bonuses_) {
		if (player->hasBonus(bonus->type(), bonus->tier())) {
			ret.append(qMakePair(bonus->type(), bonus->tier()));
		}
	}
	
	return ret;
}

bool BonusManager::canApply(Player *player, BonusType type, SNTypes::tier tier) {
	return getBonus(type, tier)->canApply(player);
}

void BonusManager::applyBonus (Player *player, BonusType type, SNTypes::tier tier) {
	player->applyBonus(type, tier);
	GameManager::get()->checkIfWin(player, WinCondition::Technology);
}

void BonusManager::tryToApplyBonus(int bonus)
{
	if(bonuses_[bonus]->canApply(GameManager::get()->currentPlayer())){
		applyBonus(GameManager::get()->currentPlayer(),bonuses_[bonus]->type(), bonuses_[bonus]->tier());
// 		qDebug() <<"applied " << bonus;
		
	}
	emit bonusesUpdated();
}

bool BonusManager::isApplied(int bonus)
{
	
	return GameManager::get()->currentPlayer()->hasBonus(bonuses_[bonus]);
}

bool BonusManager::isAffordable(int bonus)
{
	return bonuses_[bonus]->canApply(GameManager::get()->currentPlayer());
}

void BonusManager::reloadBonuses()
{
	emit bonusesUpdated();
}


