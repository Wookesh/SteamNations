#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <QObject>
#include "Bonuses/Bonuses.hpp"
#include "Serial.hpp"
#include <QString>
#include "EnumHelpers.hpp"
#include "SNTypes.hpp"
#include "Config.hpp"
#include "SNCore/Actions/Action.hpp"
#include "SNCore/Objects/Prototypes/Prototype.hpp"

#define GMlog() GameManager::get()->console()->in()

class Action;
class Console;
class Board;
class Object;
class Player;
class Tile;
class Unit;
class Town;

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
	
	Q_INVOKABLE bool useSettings(int width, int height, int playersCount, const QStringList &names, const QList<bool> &computers, const QVariantList &colors);
	void initBoard(int width, int height, int seed = time(NULL));
	Q_INVOKABLE void endGame();
	
	Q_INVOKABLE bool load(const QString &saveFile = QDir::home().absolutePath() + "/.SNSave");
	Q_INVOKABLE void save(const QString &saveFile = QDir::home().absolutePath() + "/.SNSave");
	
	QList<Player *> players() const;
	void setPlayers(QList<Player *> &players);
	
	Board *board() const;
	void setBoard(Board *board);
	
	Console *console() const;

	Player *currentPlayer() const;
	int currentTurn() const;
	Player *player(const QString &name);
	Q_INVOKABLE QString currentPlayerName();
	
	void addObject(Object *object);
	const Object *object(UID uid) const;
	bool exists(UID uid) const;
	
	QVector<Action *> mapActions(const Object *object);
	QVector<Action *> objectActions(const Object *object);
	Action *getUnitAction(Unit *unit, ActionType action, Tile *tile);
	Action *getProduceAction(Town *town, PrototypeType prototype);
	
	SNTypes::population totalPopulation() const;
	SNTypes::amount totalGold() const;
	SNTypes::amount totalGoldIncome() const;
	
	void checkIfWin(Player *player, WinCondition condition);
	
	void updateResources();
	
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
	void emitEndIfWin(bool result, Player *player, QString winType);
	bool loadPlayers(QDataStream &in);
	void savePlayers(QDataStream &out);
	bool loadBoard(QDataStream &in);
	bool loadObjects(QDataStream &in);
	void saveObjects(QDataStream &out);
	bool loadTown(QDataStream &in, unsigned int posX, unsigned int posY, Player *owner);
	bool loadUnit(QDataStream &in, unsigned int posX, unsigned int posY, Player *owner);
	
public slots:
	void removeObject(UID uid);
	void startGame();
	void endTurn();
	void check(const QString playerName);
	
signals:
	void turnEnded();
	void gameInitialized();
	void gameEnded(const QString winnerName, const QString type);
	void updateResourcesSignal();
	void turnReady();
	void objectCreated(UID uid);
	
friend class Console;
};

#endif

