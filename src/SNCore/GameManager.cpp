#include "GameManager.hpp"
#include "Object.hpp"
#include "Soldier.hpp"
#include "Settler.hpp"
#include "AttackAction.hpp"
#include "MoveAction.hpp"
#include "CaptureAction.hpp"
#include "SettleAction.hpp"
#include "CreateUnitAction.hpp"
#include "Town.hpp"

GameManager *GameManager::instance = 0;

GameManager *GameManager::get() {
	if (instance == nullptr) {
		// TODO: Add a proper exception
		throw;
	}
	return instance;
}

void GameManager::init() {
	clean();
	instance = new GameManager();
}

void GameManager::clean() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

GameManager::GameManager(QObject *parent): QObject(parent), serial_(new Serial())
{

}

GameManager::~GameManager()
{

}

Serial *GameManager::serial()
{
	return serial_;
}

void GameManager::addObject(UID uid, Object *object)
{
	objects_[uid] = object;
	emit objectCreated(uid);
	connect(object, &Object::objectDestroyed, this, &GameManager::removeObject);
}

void GameManager::removeObject(UID uid)
{
	objects_.remove(uid);
}


Object *GameManager::objectP(UID uid)
{
	return objects_[uid];
}

const Object *GameManager::object(UID uid) const
{
	return objects_[uid];
}


Board *GameManager::board() const
{
	return board_;
}

void GameManager::setBoard(Board *board)
{
	board_ = board;
}

QList< Player * > GameManager::players() const
{
	return players_;
}

QVector<Action *> GameManager::objectActions(const Object *objectC)
{
	Object *objectN = objectP(objectC->id());
	QVector<Action *> possibleActions;
	switch(objectN->type()) {
		case Object::Type::Town:
		{
			Town *town = dynamic_cast<Town *>(objectN);
			//przydałaby się jakaś lista typów żeby fora zrobić jak będzie więcej jednostek
			if(town->canRecruit(Prototype::Type::Settler))
				possibleActions.push_back(new CreateUnitAction(town, Prototype::Type::Settler));
			if(town->canRecruit(Prototype::Type::Soldier))
				possibleActions.push_back(new CreateUnitAction(town, Prototype::Type::Soldier));
			
			return possibleActions;
		}
		default:
		{
			return possibleActions;
		}
	}
}

QVector<Action *> GameManager::mapActions(const Object *objectC)
{
	Object *objectN = objectP(objectC->id());
	QVector<Action *> possibleActions;
	switch(objectN->type()) {
		case Object::Type::Unit:
		{
			Unit *unit = dynamic_cast<Unit *>(objectN);
			QVector<Tile *> tiles = board_->getInRange(unit->tile(), unit->currentMoveRange());
			for (Tile *currTile : tiles) {
				if (unit->canMove(currTile))
					possibleActions.push_back(new MoveAction(unit, currTile));
				
				if (unit->pType() == Prototype::Type::Soldier) {
					if (dynamic_cast<Soldier *>(unit)->canAttack(currTile))
						possibleActions.push_back(new AttackAction(dynamic_cast<Soldier *>(unit), currTile->unit()));
					
					if (dynamic_cast<Soldier *>(unit)->canCapture(currTile))
						possibleActions.push_back(new CaptureAction(dynamic_cast<Soldier *>(unit), currTile->town()));
				}
				
				if (unit->pType() == Prototype::Type::Settler)
					if (dynamic_cast<Settler *>(unit)->canSettle(currTile))
						possibleActions.push_back(new SettleAction(dynamic_cast<Settler *>(unit)));
			}
			return possibleActions;
		}
		default:
		{
			return possibleActions;
		}
	}
}


void GameManager::setPlayers(QList< Player * > &players)
{

}

void GameManager::initGame()
{

}

void GameManager::startGame()
{

}

void GameManager::endGame()
{

}

void GameManager::endTurn()
{

}


int GameManager::currentTurn() const
{
	return currentTurn_;
}

Player *GameManager::currentPlayer() const
{
	return currentPlayer_;
}

void GameManager::setNextPlayer()
{

}

void GameManager::checkIfWin()
{

}

void GameManager::setWinConditions()
{

}