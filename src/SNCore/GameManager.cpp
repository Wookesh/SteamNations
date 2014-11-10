#include "GameManager.hpp"
#include "Object.hpp"
#include "Soldier.hpp"
#include "Settler.hpp"
#include "AttackAction.hpp"
#include "MoveAction.hpp"
#include "CaptureAction.hpp"
#include "SettleAction.hpp"

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
}

Object *GameManager::object(UID uid)
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

QVector<Action *> GameManager::actions(const Object *objectC)
{
	Object *objectN = object(objectC->id());
	switch(objectN->type()) {
		case Object::Type::Unit:
			Unit *unit = dynamic_cast<Unit *>(objectN);
			QVector<Tile *> tiles = board_->getInRange(unit->tile(), unit->currentMoveRange());
			QVector<Action *> unitActions;
			for (Tile *currTile : tiles) {
				if (unit->canMove(currTile))
					unitActions.push_back(new MoveAction(unit, currTile));
				
				if (unit->pType() == Prototype::Type::Soldier) {
					if (dynamic_cast<Soldier *>(unit)->canAttack(currTile))
						unitActions.push_back(new AttackAction(dynamic_cast<Soldier *>(unit), currTile->unit()));
					
					if (dynamic_cast<Soldier *>(unit)->canCapture(currTile))
						unitActions.push_back(new CaptureAction(dynamic_cast<Soldier *>(unit), currTile->town()));
				}
				
				if (unit->pType() == Prototype::Type::Settler)
					if (dynamic_cast<Settler *>(unit)->canSettle())
						unitActions.push_back(new SettleAction(dynamic_cast<Settler *>(unit)));
			}
			return unitActions;
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