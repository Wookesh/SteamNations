#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <QObject>
#include "Player.hpp"
#include "Board.hpp"

class GameManager : public QObject {
Q_OBJECT
public:
	static GameManager *get();
	static void init();
	static void clean();
	
	void initGame();
	void endGame();
	
	QList<Player *> players() const;
	void setPlayers(QList<Player *> &players);
	
	Board *board() const;
	void setBoard(Board *board);
	
	Player *currentPlayer() const;
	int currentTurn() const;
	
protected:
	GameManager(QObject *parent = nullptr);
	virtual ~GameManager();
	
private:
	static GameManager *instance;
	QList<Player *> players_;
	Player *currentPlayer_;
	Board *board_;
	int currentTurn_;
	Object *selectedObject;
	void setNextPlayer();
	void setWinConditions();
	
public slots:
	void startGame();
	void checkIfWin();
	void endTurn();
	
signals:
	void gameInitialized();
	void gameEnded();
	void turnReady();
};

#endif