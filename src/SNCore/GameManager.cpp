#include "GameManager.hpp"

GameManager::GameManager(QObject *parent): QObject(parent)
{

}

GameManager::~GameManager()
{

}


Board *GameManager::board() const
{

}

void GameManager::setBoard(Board *board)
{

}

QList< Player * > GameManager::players() const
{

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

}

Player *GameManager::currentPlayer() const
{

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