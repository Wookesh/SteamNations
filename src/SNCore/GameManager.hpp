#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <QObject>
#include "Serial.hpp"
#include <QString>
#include "EnumHelpers.hpp"
#include "SNTypes.hpp"
#include "Config.hpp"

#define GMlog() GameManager::get()->console()->in()

class Action;
class Console;
class Board;
class Object;
class Player;

EnumClassWithStrings(WinCondition, quint8, Domination, Technology, Conquest, Economic, Any)

class GameManager : public QObject {
Q_OBJECT
public:
	Q_PROPERTY(GameManager * gameManagerInstance READ get)
	Q_PROPERTY(int turn READ currentTurn)
	Q_PROPERTY(Console *console READ console)
	static GameManager *get();
	static void init();
	static void clean();
	
	Q_INVOKABLE bool useSettings(int width, int height, int playersCount, const QStringList &names, const QVariantList &colors);
	void initBoard(int width, int height, int seed = qrand());
	Q_INVOKABLE void endGame();
	
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
	
	SNTypes::population totalPopulation() const;
	SNTypes::amount totalGold() const;
	SNTypes::amount totalGoldIncome() const;
	
	void checkIfWin(Player *player, WinCondition condition);
	
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
	QList<Player *>::iterator playerIterator_;
	
	void setNextPlayer();
	void prepareNewTurn();
	void setWinConditions();
	Object *objectP(UID uid);
	void emitEndIfWin(bool result, Player *player);
	bool loadPlayers(QDataStream &in);
	void savePlayers(QDataStream &out);
	bool loadBoard(QDataStream &in);
	
public slots:
	void removeObject(UID uid);
	void startGame();
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

