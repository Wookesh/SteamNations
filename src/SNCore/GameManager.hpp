#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <QObject>
#include "Serial.hpp"
#include <QString>

#define GMlog() GameManager::get()->console()->in()

class Action;
class Console;
class Board;
class Object;
class Player;

class GameManager : public QObject {
Q_OBJECT
public:
	Q_PROPERTY(GameManager * gameManagerInstance READ get)
	Q_PROPERTY(int turn READ currentTurn)
	Q_PROPERTY(Console *console READ console)
	static GameManager *get();
	static void init();
	static void clean();
	
	void initGame(int width, int height, int seed = qrand());
	void endGame();
	
	void load(const QString &saveFile);
	void save(const QString &saveFile);
	void errorLoading();
	
	QList<Player *> players() const;
	void setPlayers(QList<Player *> &players);
	
	Board *board() const;
	void setBoard(Board *board);
	
	Console *console() const;

	Player *currentPlayer() const;
	int currentTurn() const;
	
	void addObject(Object *object);
	const Object *object(UID uid) const;
	bool exists(UID uid) const;
	
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
	Console *console_;
	
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
	void turnEnded();
	void gameInitialized();
	void gameEnded(const Player *winner);
	void turnReady();
	void objectCreated(UID uid);
	
friend class Console;
};

class GameManagerInstanceBox : public QObject {
Q_OBJECT
public:
	Q_PROPERTY(GameManager *gameManager READ gm)
	GameManager *gm();
};

#endif
