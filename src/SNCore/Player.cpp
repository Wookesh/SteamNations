#include "Player.hpp"
#include "Console.hpp"
#include "Objects/Prototypes/Prototypes.hpp"
#include "Objects/Town.hpp"
#include "Objects/Unit.hpp"
#include "Tile.hpp"
#include "Config.hpp"
#include "GameManager.hpp"
#include "Board.hpp"

#include <QtCore>

const QHash<Resource, SNTypes::amount> Player::BASE_BUILDING_COST = {
	{Resource::Gold, SNCfg::BUILDING_GOLD_COST},
	{Resource::Research, SNCfg::BUILDING_RESEARCH_COST},
	{Resource::Food, SNCfg::BUILDING_FOOD_COST}
};

Player::Player(const QString &name, QColor color) : capital_(nullptr), name_(name), color_(color)
{
	prototypes_[PrototypeType::Infantry] = new SoldierPrototype(PrototypeType::Infantry);
	prototypes_[PrototypeType::Heavy] = new SoldierPrototype(PrototypeType::Heavy);
	prototypes_[PrototypeType::Artillery] = new SoldierPrototype(PrototypeType::Artillery);
	soldierPrototypes_ = prototypes_;
	prototypes_[PrototypeType::Settler] = new SettlerPrototype();
	
	for (Resource r : Resource::labels())
		resources_[r] = 0;
	
	bonuses_ = {
		{BonusType::War, {{1, false}, {2, false}, {3, false}}},
		{BonusType::Def, {{1, false}, {2, false}, {3, false}}},
		{BonusType::Eco, {{1, false}, {2, false}, {3, false}}}
	};
	
	buildingCost_ = BASE_BUILDING_COST;
	lastIncome_[Resource::Gold] = 0;
	lastIncome_[Resource::Research] = 0;
}

Player::~Player()
{
	qDeleteAll(prototypes_);
	prototypes_.clear();
	
	units_.clear();
	towns_.clear();
}

QString Player::name() const
{
	return name_;
}

QColor Player::color() const
{
	return color_;
}


void Player::obtainTown(Town *town)
{
	towns_.push_back(town);
}

void Player::destroyTown (Town *town) {
	for (auto iter = towns_.begin(); iter != towns_.end(); ++iter) {
		if (*(iter) == town) {
			towns_.erase(iter);
			break;
		}
	}
}

unsigned int Player::getTownCount() 
{
	return towns_.count();
}

unsigned int Player::getUnitsCount()
{
	return units_.count();
}


unsigned int Player::resource(Resource resource) const
{
	return resources_[resource];
}

void Player::addResource(Resource resource, unsigned int val)
{
	qDebug() << "Player" << name() << "received" << val << "of" << QString(resource);
	resources_[resource] += val;
}

bool Player::removeResource(Resource resource, unsigned int val)
{
	if (resources_[resource] >= val) {
		resources_[resource] -= val;
		return true;
	}
	return false;
}

void Player::updateBefore()
{
	// internal stuff
	// doSth()...
	SNTypes::amount gold = resource(Resource::Gold);
	SNTypes::amount research = resource(Resource::Research);
	
	// Units
	for (auto unit : units_) {
		unit->updateBefore();
	}
	
	// Towns
	for (auto town : towns_) {
		town->updateBefore();
	}
	
	lastIncome_[Resource::Gold] = resource(Resource::Gold) - gold;
	lastIncome_[Resource::Research] = resource(Resource::Research) - research;
	
	GameManager::get()->checkIfWin(this, WinCondition::Domination);
	GameManager::get()->checkIfWin(this, WinCondition::Economic);
	// internal stuff
	// wrapUp()...
}

void Player::updateAfter()
{
	// internal stuff
	// doSth()...
	
	// Units
	for (auto unit : units_) {
		unit->updateAfter();
	}
	
	// Towns
	for (auto town : towns_) {
		town->updateAfter();
	}
	
	// internal stuff
	// wrapUp()...
}

Town *Player::capital() 
{
	return capital_;
}

void Player::setCapital (Town *town) 
{
	capital_ = town;
}

Unit *Player::createUnit(PrototypeType type, Tile *tile) 
{
	Unit *newUnit = prototypes_[type]->createUnit(tile, this);
	units_.push_back(newUnit);
	tile->setUnit(newUnit);
	
	return newUnit;
}

void Player::destroyUnit(Unit *toKill) 
{
	for (auto iter = units_.begin(); iter != units_.end(); ++iter) {
		if (*(iter) == toKill) {
			units_.erase(iter);
			break;
		}
	}
}

Prototype *Player::prototype(PrototypeType type)
{
	return prototypes_[type];
}

QList< Prototype * > Player::prototypes() 
{
	return prototypes_.values();
}

QList< Prototype * > Player::soldierPrototypes() 
{
	return soldierPrototypes_.values();
}

bool Player::applyBonus(BonusType type, SNTypes::tier tier) 
{
	Bonus *bonus = BonusManager::get()->getBonus(type, tier);
	if (bonus->apply(this)) {
		bonuses_[bonus->type()][bonus->tier()] = true;
		removeResource(Resource::Research, bonus->cost());
		return true;
	} else
		return false;
}

bool Player::hasBonus(BonusType type, SNTypes::tier tier) const
{
	return bonuses_[type][tier];
}

bool Player::canAffordBuilding(Resource type)
{
	return buildingCost_[type] <= resources_[Resource::Gold];
		
}

void Player::payForBuilding(Resource type)
{
	resources_[Resource::Gold] -= buildingCost_[type];
}

bool Player::hasBonus(Bonus* bonus)
{
	return hasBonus(bonus->type(), bonus->tier());
}

int Player::nOfTowns() {
	return towns_.size();
}

SNTypes::population Player::population() const
{
	SNTypes::population ret = 0;
	
	for (Town *town : towns_)
		ret += town->population();
	
	return ret;
}

unsigned int Player::landSize() const
{
	unsigned int ret = 0;
	
	for (Town *town : towns_)
		ret += town->size();
	
	return ret;
}

SNTypes::amount Player::lastIncome(Resource resource) const
{
	if (resource != Resource::Gold && resource != Resource::Research)
		return 0;
	
	return lastIncome_[resource];
}

bool Player::load(QDataStream &in)
{
	for (PrototypeType prototype: PrototypeType::labels())
		if (!prototypes_[prototype]->load(in)) return false;
	
	for (Resource r : Resource::labels())
		in >> resources_[r];
	
	for (BonusType bType: BonusType::labels())
		in >> bonuses_[bType];
	
	for (Resource r : buildingCost_.keys())
		in >> buildingCost_[r];
	
	for (Resource r : lastIncome_.keys())
		in >> lastIncome_[r];
	return true;
}

bool Player::save(QDataStream &out)
{
	for (PrototypeType prototype: PrototypeType::labels())
		prototypes_[prototype]->save(out);
	
	for (Resource r : Resource::labels())
		out << resources_[r];
	
	for (BonusType bType: BonusType::labels())
		out << bonuses_[bType];
	
	for (Resource r : buildingCost_.keys())
		out << buildingCost_[r];
	
	for (Resource r : lastIncome_.keys())
		out << lastIncome_[r];
	
	return true;
}

HumanPlayer::HumanPlayer(const QString &name, QColor color) : Player(name, color) 
{

}

HumanPlayer::~HumanPlayer() 
{

}

void HumanPlayer::performTurn() 
{
	qDebug() << "HumanPlayer";
}

void ComputerPlayer::performTurn() 
{
	qDebug() << "ComputerPlayer";
	for (Unit *unit : units_) {
		qDebug() << unit->name() << unit->tile()->position();
		QPair<ActionType, Tile *> target = unit->getTargetWithAction();
		qDebug() << "Start to perform action: " << target.second->position().x() << target.second->position().y() << (QString)(target.first);
		QVector<Tile *> path = GameManager::get()->board()->pathToTile(unit->tile(), target.second);
		path.pop_back();
		bool canDoSomething = true;
		do {
			if (unit->canPerform(target.first, target.second)) {
				Action *action = GameManager::get()->getUnitAction(unit, target.first, target.second);
				if (action)
					action->perform();
				else
					qDebug() << "ERROR";
				canDoSomething = false;
			} else if (!path.isEmpty() && unit->canMove(path.last())) {
				Action *action = GameManager::get()->getUnitAction(unit, ActionType::Move, path.last());
				if (action)
					action->perform();
				else
					qDebug() << "ERROR";
				path.pop_back();
			} else {
				canDoSomething = false;
			}
		} while (canDoSomething);
	}
	GameManager::get()->endTurn();
}

ComputerPlayer::ComputerPlayer (const QString& name, QColor color) : Player (name, color) 
{

}

ComputerPlayer::~ComputerPlayer() 
{

}

bool Player::hasSettler() {
	for (Unit *unit : units_) {
		if (unit->pType() == PrototypeType::Settler) {
			return true;
		}
	}
	return false;
}


Tile *Player::centralPositon() {
	if (capital_ != nullptr)
		return capital_->tile();
	
	if (!units_.empty())
		return units_[0]->tile();
	
	// Should never reach this point!
	return GameManager::get()->board()->getTile(0, 0);
}

