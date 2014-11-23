#include "Player.hpp"
#include "Objects/Prototypes/SettlerPrototype.hpp"
#include "Objects/Prototypes/SoldierPrototype.hpp"
#include "Objects/Town.hpp"
#include "Objects/Unit.hpp"
#include "Tile.hpp"
#include "Objects/Prototypes/Prototype.hpp"

#include <QtCore>

Player::Player(const QString &name, Qt::GlobalColor color) : capital_(nullptr), name_(name), color_(color)
{
	prototypes_[ProtoType::Settler] = new SettlerPrototype();
	prototypes_[ProtoType::Soldier] = new SoldierPrototype();
	
	for (Resource r : Resource::labels())
		resources_[r] = 0;
}

Player::~Player()
{
	for (auto element : prototypes_.keys()) {
		Prototype *aux = prototypes_.take(element);
		delete aux;
	}
	
	while (!units_.isEmpty()) {
		Unit *aux = units_.takeLast();
		delete aux;
	}
	
	while (!towns_.isEmpty()) {
		Town *aux = towns_.takeLast();
		delete aux;
	}
}

QString Player::name() const
{
	return name_;
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

Qt::GlobalColor Player::color() const
{
	return color_;
}

unsigned int Player::getTownCount() {
	return towns_.count();
}

unsigned int Player::resource(Resource resource) const
{
	return resources_[resource];
}

void Player::addResource(Resource resource, unsigned int val)
{
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

void Player::updateBefore() {
	// internal stuff
	// doSth()...
	
	// Units
	for (auto unit : units_) {
		unit->updateBefore();
	}
	
	// Towns
	for (auto town : towns_) {
		town->updateBefore();
	}
	
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


Unit *Player::createUnit(ProtoType type, Tile *tile) {
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


Prototype *Player::prototype(ProtoType type)
{
	return prototypes_[type];
}
