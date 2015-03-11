#include "Unit.hpp"
#include "../Tile.hpp"
#include "Prototypes/Prototype.hpp"
#include "../GameManager.hpp"
#include "../Board.hpp"
#include "Player.hpp"
#include "Object.hpp"
#include "Town.hpp"
#include "SNCore/Console.hpp"


Unit::Unit(Tile *tile, const Prototype *prototype, Player *owner, QObject *parent) :
    Object(tile, ObjectType::Unit, owner, parent),
	prototype_(prototype),
	actionPointsLeft_(0),
	healthLeft_(prototype->health())
{
	updateVision();
}

Unit::~Unit()
{
	if (tile_ != nullptr)
		tile_->setUnit(nullptr);
}

void Unit::updateBefore() 
{
	actionPointsLeft_ = actionPoints();
}

void Unit::updateAfter()
{
	
}

QString Unit::name() const
{
	return prototype_->name();
}

PrototypeType Unit::pType() const
{
	return prototype_->type();
}

SNTypes::ap Unit::actionPoints() const
{
	return prototype_->actionPoints();
}

SNTypes::ap Unit::actionPointsLeft() const
{
	return actionPointsLeft_;
}

void Unit::spentActionPoints(SNTypes::ap actionPoints)
{
	actionPointsLeft_ -= actionPoints;
}

SNTypes::hp Unit::health() const
{
	return prototype_->health();
}

SNTypes::hp Unit::healthLeft() const
{
	return healthLeft_;
}

bool Unit::canMove(const Tile *tile) const
{
	if (tile->unit() == nullptr && 
		GameManager::get()->board()->getAbsoluteDistance(tile, tile_) <= actionPointsLeft() &&
		GameManager::get()->currentPlayer() == owner() &&
		(tile->town() == nullptr ? true : tile->town()->owner() == owner()))
		return true;
	return false;
}

bool Unit::move(Tile *tile, SNTypes::ap moveCost)
{
	if (canMove(tile)) {
		spentActionPoints(moveCost);
		tile_->setUnit(nullptr);
		tile->setUnit(this);
		setTile(tile);
		updateVision();
		emit positionChanged();
		return true;
	}
	return false;
}

void Unit::removeHealth(SNTypes::dmg damage) 
{
	healthLeft_ = damage >= healthLeft_ ? 0 : healthLeft_ - damage;
	if (!healthLeft_) {
		owner_->destroyUnit(this);
	}
}

bool Unit::checkForDeath() 
{
	return healthLeft_ <= 0;
}

void Unit::updateVision()
{
	QVector<Tile *> tiles = GameManager::get()->board()->getInRange(tile(), prototype_->visionRange());
	for (Tile *tile : tiles) {
		tile->setVisionState(owner(), VisionType::Visible);
	}
}
