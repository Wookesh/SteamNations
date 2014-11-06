#include "GameManager.hpp"

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

}

QList< Player * > GameManager::players() const
{
	return players_;
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