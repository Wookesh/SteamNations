#include "GameManager.hpp"
#include "Objects/Object.hpp"
#include "Objects/Soldier.hpp"
#include "Objects/Settler.hpp"
#include "Actions/AttackAction.hpp"
#include "Actions/MoveAction.hpp"
#include "Actions/CaptureAction.hpp"
#include "Actions/SettleAction.hpp"
#include "Actions/CreateUnitAction.hpp"
#include "Objects/Town.hpp"
#include "Objects/Prototypes/SettlerPrototype.hpp"

#include <QDebug>

GameManager *GameManager::instance = nullptr;

GameManager *GameManager::get() {
	if (instance == nullptr) {
		// TODO: Add a proper exception
		throw;
	}

	return instance;
}

void GameManager::init() {
	clean();
	instance = new GameManager();
}

void GameManager::clean() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

GameManager::GameManager (QObject *parent) : QObject (parent), serial_ (new Serial()) {

}

GameManager::~GameManager() {

}

Serial *GameManager::serial() {
	return serial_;
}

void GameManager::addObject (UID uid, Object *object) {
	objects_[uid] = object;
	emit objectCreated (uid);
	connect (object, &Object::objectDestroyed, this, &GameManager::removeObject);
}

void GameManager::removeObject (UID uid) {
	objects_.remove (uid);
}


Object *GameManager::objectP (UID uid) {
	return objects_[uid];
}

const Object *GameManager::object (UID uid) const {
	return objects_[uid];
}


Board *GameManager::board() const {
	return board_;
}

void GameManager::setBoard (Board *board) {
	board_ = board;
}

QList< Player * > GameManager::players() const {
	return players_;
}

QVector<Action *> GameManager::objectActions (const Object *objectC) {
	Object *objectN = objectP (objectC->id());
	QVector<Action *> possibleActions;

	if (objectN->type() == ObjectType::Town) {
		Town *town = dynamic_cast<Town *> (objectN);

		for (ProtoType type : ProtoType::labels())
			if (town->canRecruit(type))
				possibleActions.push_back(new CreateUnitAction(town, type));

	} else if (objectN->type() == ObjectType::Unit) {
		Unit *unit = dynamic_cast<Unit *> (objectN);

		if (unit->pType() == ProtoType::Settler)
			if (dynamic_cast<Settler *> (unit)->canSettle(unit->tile()))
				possibleActions.push_back(new SettleAction(dynamic_cast<Settler *> (unit)));
	}
	return possibleActions;
}

QVector<Action *> GameManager::mapActions (const Object *objectC) {
	Object *objectN = objectP (objectC->id());
	QVector<Action *> possibleActions;

	if (objectN->type() == ObjectType::Unit) {
		Unit *unit = dynamic_cast<Unit *> (objectN);
		QVector<Tile *> tiles = board_->getInRange (unit->tile(), unit->currentMoveRange());

		for (Tile * currTile : tiles) {
			if (unit->canMove (currTile))
				possibleActions.push_back (new MoveAction (unit, currTile));

			if (unit->pType() == ProtoType::Soldier) {
				Soldier *soldier = static_cast<Soldier *>(unit);
				if (soldier->canAttack (currTile))
					possibleActions.push_back (new AttackAction (soldier, currTile->unit()));

				if (soldier->canCapture (currTile))
					possibleActions.push_back (new CaptureAction (soldier, currTile->town()));
			}
		}
	}
	return possibleActions;
}


void GameManager::setPlayers (QList< Player * > &players) {
	players_ = players; //nie jestem pewien czy nie trzeba czegos usuwac
}

void GameManager::initGame() {
	// Test players
	Player *andrzej = new Player ("Andrzej", Qt::black);
	Player *zbyszek = new Player ("Zbyszek", Qt::darkBlue);
	
	QList<Player *> lista;
	lista.push_back (andrzej);
	lista.push_back (zbyszek);
	setPlayers (lista);
	
	currentPlayer_ = andrzej;
	
	Board *board = GameManager::get()->board();
	
	andrzej->createUnit(ProtoType::Settler, board->getTile(25, 25));
	andrzej->updateAfter(); //aby jednostka mogła się poruszać
	zbyszek->createUnit(ProtoType::Settler, board->getTile(24, 26));
	zbyszek->updateAfter();
	
	QObject::connect(this, SIGNAL(gameEnded(Player*)),
					 this, SLOT(check(Player*)));
}

void GameManager::check (Player *player) {
	qDebug() << "Game won by " << player->color() << "\n";
}

void GameManager::startGame() {

}

void GameManager::endGame() {

}

void GameManager::endTurn() {
	currentPlayer_->updateAfter();
	setNextPlayer();
	currentTurn_++;
	currentPlayer_->updateBefore();
	turnReady();
}


int GameManager::currentTurn() const {
	return currentTurn_;
}

Player *GameManager::currentPlayer() const {
	return currentPlayer_;
}

void GameManager::setNextPlayer() {
	QList<Player *>::iterator it = players_.begin();

	while ( (*it) != currentPlayer())
		it++;

	it++;

	if (it == players_.end())
		it = players_.begin();

	currentPlayer_ = *it;
}

void GameManager::checkIfWin(Player *player) {
	qDebug() << "Checking if " << player->color() << " has won the game";
	if (player->getTownCount() >= 3) {
		emit gameEnded(player);
	}
}

void GameManager::setWinConditions() {

}
