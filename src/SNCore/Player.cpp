#include "Player.hpp"
#include "SettlerPrototype.hpp"
#include "Town.hpp"
#include "Unit.hpp"

#include <QtCore>

Player::Player(const QString &name) : name_(name)
{
	SettlerPrototype *settlerPrototype = new SettlerPrototype(
		BASE_SETTLER_NAME, BASE_SETTLER_MOVERANGE, BASE_SETTLER_COST);
	prototypes_[Prototype::Type::Settler] = settlerPrototype;
}

Player::~Player()
{
	for (auto element : prototypes_.keys()) {
		Prototype *aux = prototypes_.take(element);
		delete aux;
	}
}

QString Player::name() const
{
	return name_;
}

void Player::obtainTown (Town *town) 
{
	town->setOwner(this);
	towns_.push_back(town);
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

Unit *Player::createUnit (Prototype::Type type, Tile *tile) {
	//Unit *newUnit = prototypes_[type]->createUnit(tile);
	//units_.push_back(newUnit);
	
	//return newUnit;
	return nullptr;
}

Prototype *Player::prototype(Prototype::Type type)
{
	return prototypes_[type];
}
