#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <QObject>
#include "Player.hpp"
#include "Board.hpp"
#include "Object.hpp"
#include "Action.hpp"
#include "Serial.hpp"

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
	
	Serial *serial();
	
	void addObject(UID uid, Object *object);
	const Object *object(UID uid) const;
	
	Object *object(UID uid);
	QVector<Action *> actions(const Object *object);
	
protected:
	GameManager(QObject *parent = nullptr);
	virtual ~GameManager();
	
private:
	static GameManager *instance;
	QList<Player *> players_;
	Player *currentPlayer_;
	Board *board_;
	Serial *serial_;
	int currentTurn_;
	QHash<UID,Object *> objects_;
	void setNextPlayer();
	void setWinConditions();
	
public slots:
	void removeObject(UID uid);
	void startGame();
	void checkIfWin();
	void endTurn();
	
signals:
	void gameInitialized();
	void gameEnded();
	void turnReady();
	void objectCreated(UID uid);
};

#endif