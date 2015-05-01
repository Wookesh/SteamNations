#include "GameManager.hpp"
#include "Board.hpp"
#include "Console.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Objects/Objects.hpp"
#include "Actions/Actions.hpp"

#include <QDebug>
#include <QDateTime>

GameManager *GameManager::instance = nullptr;

GameManager *GameManager::get() 
{
	if (instance == nullptr) {
		init();
	}

	return instance;
}

void GameManager::init() 
{
	clean();
	instance = new GameManager();
	qsrand(QDateTime::currentDateTime().toTime_t());
}

void GameManager::clean() 
{
	if (instance != nullptr) {
		GameManager *aux = instance;
		instance = nullptr;
		delete aux;
	}
}

GameManager::GameManager(QObject *parent) : QObject(parent),
	currentPlayer_(nullptr), board_(nullptr), serial_(new Serial()), currentTurn_(0), console_(new Console())
{
	BonusManager::init();
}

GameManager::~GameManager() 
{

}

bool GameManager::loadPlayers(QDataStream &in)
{
	int playersCount;
	in >> playersCount;
	if (playersCount < 2 || playersCount > 4)
		return false;
	
	for (int i = 0; i < playersCount; ++i) {
		QString playerName;
		QColor playerColor;
		bool isComputer;
		in >> playerName >> playerColor >> isComputer;
		Player *player = nullptr;
		if (isComputer)
			player = new ComputerPlayer(playerName, playerColor);
		else
			player = new HumanPlayer(playerName, playerColor);
		players_.push_back(player);
		
		if (!player->load(in)) return false;
	}
	
	QString currentPlayerSaved;
	in >> currentPlayerSaved;
	playerIterator_ = players_.begin();
	while (playerIterator_ != players_.end() && (*playerIterator_)->name() != currentPlayerSaved)
		++playerIterator_;
	if (playerIterator_ == players_.end())
		return false;
	
	currentPlayer_ = *playerIterator_;
	
	return true;
}

void GameManager::savePlayers(QDataStream &out)
{
	out << players_.count();
	for (Player *player : players_) {
		out << player->name() << player->color();
		player->save(out);
	}
	out << (*playerIterator_)->name();
}

bool GameManager::loadBoard(QDataStream &in)
{
	Board *possibleBoard = new Board(10, 10); // Wookesh NOTE: maybe change it to some other value or make default constructor
	if (!possibleBoard->load(in)) {
		delete possibleBoard;
		return false;
	}
	
	if (board_ != nullptr)
		delete board_;
	board_ = possibleBoard;
	
	return true;
}

bool GameManager::loadObjects(QDataStream &in)
{
	int objectsCount;
	in >> objectsCount;
	
	for (int i = 0; i < objectsCount; ++i) {
		ObjectType objectType = ObjectType::Unit; // Wookesh NOTE: No default value
		unsigned int posX, posY;
		QString ownerName;
		in >> objectType >> posX >> posY >> ownerName;
		
		if (posX > board_->width() || posY > board_->height())
			return false;
	
		if (player(ownerName) == nullptr)
			return false;
		
		if (objectType == ObjectType::Unit) {
			if (!loadUnit(in, posX, posY, player(ownerName))) return false;
		} else if (objectType == ObjectType::Town) {
			if (!loadTown(in, posX, posY, player(ownerName))) return false;
		}
	}
	
	return true;
}

void GameManager::saveObjects(QDataStream &out)
{
	out << objects_.count();
	/* Wookesh NOTE: I've splited serialization into to parts: 
	 * 1) things we need to create object 
	 * 2) things we can assign after creation
	 * This made loadObjects() similar to this function
	 */
	for (Object *object : objects_.values()) {
		out << object->type() << object->tile()->position().x() << object->tile()->position().y() << object->owner()->name();
		if (object->type() == ObjectType::Unit)
			out << static_cast<Unit *>(object)->pType();
		object->save(out);
	}
}


bool GameManager::loadTown(QDataStream &in, unsigned int posX, unsigned int posY, Player *owner)
{
	if (!CreateTownAction(owner, board_->getTile(posX, posY)).perform())
		return false;
	
	if (!board_->getTile(posX, posY)->town()->load(in)) 
		return false;
	
	return true;
}

bool GameManager::loadUnit(QDataStream &in, unsigned int posX, unsigned int posY, Player *owner)
{
	PrototypeType type = PrototypeType::Settler;
	in >> type;

	SpawnUnitAction(owner, board_->getTile(posX, posY), type).perform();
	
	if (!board_->getTile(posX, posY)->unit()->load(in))
		return false;
	
	return true;
}

bool GameManager::load(const QString &saveFile)
{
	QFile gameSave(saveFile);
	if (gameSave.open(QIODevice::ReadOnly)) {
		QDataStream in(&gameSave);
		if (!loadPlayers(in)) return false;
		if (!loadBoard(in)) return false;
		if (!loadObjects(in)) return false;
		
		gameSave.close();
		return true;
	}
	return false;
}

void GameManager::save(const QString &saveFile)
{
	QFile gameSave(saveFile);
	if (gameSave.open(QIODevice::WriteOnly)) {
		QDataStream out(&gameSave);
		savePlayers(out);
		board_->save(out);
		saveObjects(out);
		
		gameSave.close();
	}
}

bool GameManager::useSettings(int width, int height, int playersCount, const QStringList &playerNames, const QList<bool> &computers, const QVariantList &playerColors)
{
	//Validate
	if (playerNames.size() != playersCount || playerColors.size() != playersCount)
		return false;
	
	if (playersCount < 2 || playersCount > 4)
		return false;
	
	if (width < 10 || width > 50)
		return false;
	
	if (height < 10 || height > 50)
		return false;
	
	for (QString name : playerNames)
		if (name.isEmpty())
			return false;
	
	//Create Board
	
	initBoard(width, height);
	
	//CreatePlayers
	int no = 0;
	for (QString playerName : playerNames) {
		Player *player;
		if(computers[no])
			player = new ComputerPlayer(playerName, playerColors[no].value<QColor>());
		else
			player = new HumanPlayer(playerName, playerColors[no].value<QColor>());
		players_.push_back(player);
		board_->addPlayerVisionToTiles(player);
		QPair<int, int> spawnCenter = board_->getUnitSpawnCenter(no, playersCount);
		
		SpawnUnitAction(player, board_->getTile(spawnCenter), PrototypeType::Settler).perform();
		
		spawnCenter.second += 1;
		SpawnUnitAction(player, board_->getTile(spawnCenter), PrototypeType::Infantry).perform();
		
		player->updateBefore();
		++no;
	}
	
	playerIterator_ = --players_.end();
	setNextPlayer();
	currentPlayer()->performTurn();
	return true;
}

void GameManager::initBoard(int width, int height, int seed) 
{
	if (board_ != nullptr)
		delete board_;
	board_ = new Board(width, height, seed);
	
	QObject::connect(this, &GameManager::gameEnded, this, &GameManager::check);
}

void GameManager::setPlayers(QList< Player * > &players) 
{
	players_ = players; //nie jestem pewien czy nie trzeba czegos usuwac
}

Player *GameManager::player(const QString &name)
{
	for (Player *player : players_)
		if (player->name() == name)
			return player;
	return nullptr;
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
					possibleActions.push_back(new MoveAction(unit, currTile, range));
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
					possibleActions.push_back(new CaptureAction(soldier, currTile->town(), board_->getAbsoluteDistance(soldier->tile(), currTile)));
			}
		}
	}
	return possibleActions;
}

Action *GameManager::getUnitAction(Unit *unit, ActionType action, Tile *tile)
{
	if (action == ActionType::Move) {
		return new MoveAction(unit, tile, board_->getAbsoluteDistance(tile, unit->tile()));
	}
	if (action == ActionType::Settle) {
		if (unit->pType() == PrototypeType::Settler)
			return new SettleAction(static_cast<Settler *>(unit));
		return nullptr;
	}
	if (action == ActionType::Capture) {
		if (unit->pType() == PrototypeType::Infantry && tile->town())
			return new CaptureAction(static_cast<Soldier *>(unit), tile->town(), board_->getDistance(tile, unit->tile()));
		return nullptr;
	}
	if (action == ActionType::Attack) {
		if (unit->pType() != PrototypeType::Settler && tile->unit())
			return new AttackAction(static_cast<Soldier *>(unit), tile->unit());
		return nullptr;
	}
	return nullptr;
}

Action *GameManager::getProduceAction(Town *town, PrototypeType prototype)
{
	if (town)
		return new CreateUnitAction(town, prototype);
	return nullptr;
}

void GameManager::check(const QString playerName) 
{
	GMlog() << "Game won by" << playerName;
}

void GameManager::startGame() 
{

}

void GameManager::endGame() 
{
	qDeleteAll(objects_.values());
	objects_.clear();
	
	qDeleteAll(players_);
	players_.clear();
	
	Board *tmp;
	tmp = board_;
	board_ = nullptr;
	delete tmp;
}

void GameManager::endTurn() 
{
	currentPlayer_->updateAfter();
	emit turnEnded();
	setNextPlayer();
	currentPlayer_->updateBefore();
	BonusManager::get()->reloadBonuses();
	emit turnReady();
	updateResources();
	currentPlayer()->performTurn();
}


int GameManager::currentTurn() const 
{
	return currentTurn_;
}

Player *GameManager::currentPlayer() const
{
	return currentPlayer_;
}

QString GameManager::currentPlayerName()
{
	return currentPlayer_->name();
}


void GameManager::setNextPlayer() 
{
	if (++playerIterator_ == players_.end()) {
		playerIterator_ = players_.begin();
		prepareNewTurn();
	}
	currentPlayer_ = *playerIterator_;
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

void GameManager::checkIfWin(Player *player, WinCondition condition) 
{
	if (condition == WinCondition::Conquest || condition == WinCondition::Any) {
		GMlog() << "Checking if " << player->name() << " has won the game by conquest\n";
		
		bool domination = true;
		for (Player *pl : players()) {
			// if [pl] has a capital, then check if [player] owns it
			if (pl->capital() != nullptr) {
				if (pl->capital()->owner() != player) {
					domination = false;
					break;
				}
			} else if (pl != player) { // if [pl] doesn't have a capital, check if he has any unit
				if (pl->hasAnyUnit()) {
					domination = false;
					break;
				}
			}
		}
		
		emitEndIfWin(domination, player, "conquest");
	}
	
	if (condition == WinCondition::Technology || condition == WinCondition::Any) {
		GMlog() << "Checking if " << player->name() << " has won the game by technology advancement\n";
		
		emitEndIfWin(player->hasBonus(BonusType::Eco, 3) &&
			player->hasBonus(BonusType::Def, 3) &&
			player->hasBonus(BonusType::War, 3), player, "technology advancement");
	}
	
	if (condition == WinCondition::Domination || condition == WinCondition::Any) {
		GMlog() << "Checking if " << player->name() << " has won the game by domination\n";
		float popPercentage = (float) (player->population()) / (float) (totalPopulation());
		float landPercentage = (float) (player->landSize()) / (float) (board_->size());
		
		emitEndIfWin(popPercentage > SNCfg::DOMINATION_POPULATION_WIN_CONDITION && 
			landPercentage > SNCfg::DOMINATION_LAND_WIN_CONDITION, player, "domination");
	}
	
	if (condition == WinCondition::Economic || condition == WinCondition::Any) {
		GMlog() << "Checking if " << player->name() << " has won the game by economic advantage\n";
		float goldPercentage = (float) (player->resource(Resource::Gold)) / (float) (totalGold());
		float goldIncomePercentage = (float) (player->lastIncome(Resource::Gold)) / (float) (totalGoldIncome());
		
		emitEndIfWin(goldPercentage > SNCfg::ECONOMIC_GOLD_WIN_CONDITION &&
			goldIncomePercentage > SNCfg::ECONOMIC_GOLD_INCOME_WIN_CONDITION &&
			player->resource(Resource::Gold) > SNCfg::ECONOMIC_GOLD_MIN_GOLD, player, "global economy control");
	}

}

void GameManager::emitEndIfWin(bool result, Player *player, QString winType)
{
	GMlog() << "\tWith result : " << result << "\n";
	if (result)
		emit gameEnded(player->name(), winType);
}

void GameManager::setWinConditions() 
{

}

SNTypes::population GameManager::totalPopulation() const {
	SNTypes::population ret = 0;
	
	for (Player *player : players_)
		ret += player->population();
	
	return ret;
}

SNTypes::amount GameManager::totalGold() const {
	SNTypes::amount ret = 0;
	
	for (Player *player : players_)
		ret += player->resource(Resource::Gold);
	
	return ret;
}

SNTypes::amount GameManager::totalGoldIncome() const {
	SNTypes::amount ret = 0;
	
	for (Player *player : players_)
		ret += player->lastIncome(Resource::Gold);
	
	return ret;
}

void GameManager::updateResources() {
	emit updateResourcesSignal();
}
