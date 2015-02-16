#include "GameManager.hpp"
#include "Board.hpp"
#include "Console.hpp"
#include "GameSettings.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Objects/Objects.hpp"
#include "Actions/Actions.hpp"

#include <QDebug>

GameManager *GameManager::instance = nullptr;

GameManager *GameManager::get() 
{
	if (instance == nullptr) {
		// TODO: Add a proper exception
		throw;
	}

	return instance;
}

void GameManager::init() 
{
	clean();
	instance = new GameManager();
}

void GameManager::clean() 
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

GameManager::GameManager(QObject *parent) : QObject(parent),
	currentPlayer_(nullptr), board_(nullptr), serial_(new Serial()), currentTurn_(0), console_(new Console())
{
	
}

GameManager::~GameManager() 
{

}

bool GameManager::useSettings(const GameSettings &settings)
{
	if (!settings.validate())
		return false;
	
	//Create Board
	
	initBoard(settings.boardSize.width(), settings.boardSize.height());
	
	//CreatePlayers
	
	QList<Player *> playersList;
	
	for (QPair<QString, Qt::GlobalColor> data : settings.playerData()) {
		static int no = 0;
		Player *player = new Player(data.first, data.second);
		playersList.push_back(player);
		QPair<int, int> spawnCenter = board_->getUnitSpawnCenter(no, settings.playersCount);
		
		SpawnUnitAction(player, board_->getTile(spawnCenter), PrototypeType::Settler).perform();
		spawnCenter.second += 1;
		
		SpawnUnitAction(player, board_->getTile(spawnCenter), PrototypeType::Infantry).perform();
		player->updateBefore();
		++no;
	}
	return true;
}

void GameManager::initBoard(int width, int height, int seed) 
{
	board_ = new Board(width, height, seed);
	
	QObject::connect(this, &GameManager::gameEnded, this, &GameManager::check);
}

void GameManager::setPlayers(QList< Player * > &players) 
{
	players_ = players; //nie jestem pewien czy nie trzeba czegos usuwac
}

void GameManager::addObject(Object *object) 
{
	object->setId(serial_->next());
	objects_[object->id()] = object;
	emit objectCreated(object->id());
	connect(object, &Object::objectDestroyed, this, &GameManager::removeObject);
}

void GameManager::removeObject(UID uid) 
{
	objects_.remove(uid);
}

Object *GameManager::objectP(UID uid) 
{
	return objects_[uid];
}

const Object *GameManager::object(UID uid) const 
{
	return objects_[uid];
}

bool GameManager::exists(UID uid) const
{
	return objects_.contains(uid);
}

Board *GameManager::board() const 
{
	return board_;
}

void GameManager::setBoard(Board *board) 
{
	board_ = board;
}

Console *GameManager::console() const
{
	return console_;
}

QList< Player * > GameManager::players() const 
{
	return players_;
}

QVector<Action *> GameManager::objectActions(const Object *objectC) 
{
	Object *objectN = objectP (objectC->id());
	QVector<Action *> possibleActions;

	if (objectN->type() == ObjectType::Town) {
		Town *town = dynamic_cast<Town *>(objectN);

		for (PrototypeType type : PrototypeType::labels())
			if (town->canRecruit(type))
				possibleActions.push_back(new CreateUnitAction(town, type));

	} else if (objectN->type() == ObjectType::Unit) {
		Unit *unit = dynamic_cast<Unit *>(objectN);

		if (unit->pType() == PrototypeType::Settler)
			if (dynamic_cast<Settler *>(unit)->canSettle(unit->tile()))
				possibleActions.push_back(new SettleAction(dynamic_cast<Settler *>(unit)));
	}
	return possibleActions;
}

QVector<Action *> GameManager::mapActions(const Object *objectC) 
{
	Object *objectN = objectP(objectC->id());
	QVector<Action *> possibleActions;

	if (objectN->type() == ObjectType::Unit) {
		Unit *unit = dynamic_cast<Unit *>(objectN);
		QVector<QVector<Tile *> > tiles = board_->getReachable(unit->tile(), unit->actionPointsLeft(), unit->owner());

		for (int range = 0; range < tiles.size(); ++range) {
			for (Tile * currTile : tiles[range]) {
				if (unit->canMove(currTile))
					possibleActions.push_back(new MoveAction (unit, currTile, range));
			}
		}
		
		if (unit->pType() == PrototypeType::Infantry || 
			unit->pType() == PrototypeType::Heavy ||
			unit->pType() == PrototypeType::Artillery) 
		{
			Soldier *soldier = static_cast<Soldier *>(unit);
			
			QVector<Tile *> tiles = board_->getInRange(soldier->tile(), soldier->attackRange());
			for (Tile *currTile: tiles) {
				if (soldier->canAttack(currTile))
					possibleActions.push_back(new AttackAction(soldier, currTile->unit()));

				if (soldier->canCapture(currTile))
					possibleActions.push_back(new CaptureAction(soldier, currTile->town()));
			}
		}
	}
	return possibleActions;
}

void GameManager::check(const Player *player) 
{
	GMlog() << "Game won by" << player->name();
}

void GameManager::startGame() 
{

}

void GameManager::endGame() 
{

}

void GameManager::endTurn() 
{
	currentPlayer_->updateAfter();
	emit turnEnded();
	setNextPlayer();
	currentPlayer_->updateBefore();
	emit turnReady();
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
	static QList<Player *>::iterator it = --players_.end();
	if (++it == players_.end()) {
		it = players_.begin();
		prepareNewTurn();
	}
	currentPlayer_ = *it;
	GMlog() << "----------------------------------------\n";
	GMlog() << "Player's " << currentPlayer()->name() << " turn.\n";
}

void GameManager::prepareNewTurn()
{
	GMlog() << "----------------------------------------\n";
	GMlog() << "Turn : " << currentTurn_ << "\n";
	++currentTurn_;
	board_->updateBefore();
}

void GameManager::checkIfWin(Player *player) 
{
	GMlog() << "Checking if " << player->name() << " has won the game\n";
	if (player->getTownCount() >= 3) {
		GMlog() << "\tWith result : " << true << "\n";
		emit gameEnded(player);
	}
	GMlog() << "\tWith result : " << false << "\n";
}

void GameManager::setWinConditions() 
{

}


GameManager *GameManagerInstanceBox::gm()
{
	return GameManager::get();
}
