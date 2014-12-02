#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <QObject>
#include "Serial.hpp"

class Action;
class Board;
class Object;
class Player;

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
	
	void addObject(Object *object);
	const Object *object(UID uid) const;
	
	QVector<Action *> mapActions(const Object *object);
	QVector<Action *> objectActions(const Object *object);
	
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
	void prepareNewTurn();
	void setWinConditions();
	Object *objectP(UID uid);
	
public slots:
	void removeObject(UID uid);
	void startGame();
	void checkIfWin(Player *player);
	void endTurn();
	void check(const Player *player);
	
signals:
	void gameInitialized();
	void gameEnded(const Player *winner);
	void turnReady();
	void objectCreated(UID uid);
};

#endif
