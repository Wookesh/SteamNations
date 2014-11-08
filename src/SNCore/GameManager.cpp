#include "GameManager.hpp"

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

GameManager::GameManager(QObject *parent): QObject(parent)
{

}

GameManager::~GameManager()
{

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

QList<Action * >& GameManager::actions(Object* object)
{
	switch(object->type()) {
		case Object::Type::Unit:
			Unit * unit = dynamic_cast<Unit *>(object);
			QVector<Tile *> tiles = board_->getInRange(unit->currentMoveRange());
			QVector<SN::Action *> unitActions;
			for(Tile * currTile : tiles) {
				if(unit->canMove(currTile))
					unitActions.push_back(new MoveAction(unit, currTile));
				
				if(unit->type() == Prototype::Type::Soldier) {
					if(unit->canAttack(currTile))
						unitActions.push_back(new AttackAction(dynamic_cast<Soldier *>(unit), currTile->unit()));
					if(unit->canCapture(currTile))
						unitActions.push_back(new CaptureAction(dynamic_cast<Soldier *>(unit), currTile->town()));
				}
				
				if(unit->type() == Prototype::Type::Settler)
					if(unit->canSettle(currTile))
						unitActions.push_back(new SettleAction(dynamic_cast<Settler *>(unit)));
				
			}
			return *unitActions;
		
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