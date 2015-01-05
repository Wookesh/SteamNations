#include "Console.hpp"
#include "Actions/Actions.hpp"
#include "Player.hpp"
#include "Serial.hpp"
#include "GameManager.hpp"
#include "Board.hpp"
#include "Tile.hpp"
#include "Objects/Town.hpp"
#include "Objects/Unit.hpp"
#include "Objects/Soldier.hpp"
#include <QDebug>

Console::Console(QObject *parent): QObject(parent), io_(&stringBuf_)
{
	flushingTimer_ = new QTimer(this);
	flushingTimer_->setInterval(FLUSHTIME);
	flushingTimer_->setSingleShot(false);
	connect(flushingTimer_, &QTimer::timeout, this, &Console::read);
	flushingTimer_->start();
}

Console::~Console()
{
}

void Console::read()
{
	if (io_.atEnd())
		return;
	
	for (QString s = io_.readLine(); !s.isNull(); s = io_.readLine())
		log_.push_back(s);
	emit logChanged();
}

QTextStream &Console::in()
{
	return io_;
}

void Console::flushStream()
{
	io_.flush();
}

const QStringList &Console::log()
{
	return log_;
}

void Console::addToLog(const QString &string)
{
	log_.push_back(string);
}

void Console::addToHistory(const QString &input)
{
	if (input.isEmpty())
		return;
	
	history_.push_back(input);
	emit historyChanged();
}


const QStringList &Console::history()
{
	return history_;
}

Action *Console::parseInput(const QString &input)
{
	QStringList splittedInput = input.split(" ");
	QString command = splittedInput.first();
	
	if (!ActionType::isStringCorrect(command))
		return nullptr;
	
	ActionType actionType = ActionType(command);
	
	if (actionType == ActionType::SpawnUnit) {
		if (splittedInput.size() == 5 && PrototypeType::isStringCorrect(splittedInput[1])) {
			PrototypeType unitType = PrototypeType(splittedInput[1]);
			Player *player = playerFromName(splittedInput[2]);
			Tile *tile = tileFromPos(splittedInput[3], splittedInput[4]);
			if (tile != nullptr && player != nullptr)
				return new SpawnUnitAction(player, tile, unitType);
		}
	} else if (actionType == ActionType::CreateTown) {
		if (splittedInput.size() == 4) {
			Player *player = playerFromName(splittedInput[1]);
			Tile *tile = tileFromPos(splittedInput[2], splittedInput[3]);
			if (tile != nullptr && player != nullptr)
				return new CreateTownAction(player, tile);
		}
	}
	return nullptr;
}

bool Console::parseCommand(const QString &input)
{
	static QHash<QString, void (Console::*)()> commands({
		{QString("printUnits"), &Console::printUnits},
		{QString("printTowns"), &Console::printTowns}
	});
	if (commands.contains(input)) {
		(*this.*(commands[input]))();
		return true;
	}
	return false;
}

void Console::printUnits()
{
	for (Object *o : GameManager::get()->objects_) {
		if (o->type() == ObjectType::Unit) {
			in() << o->name() << " " << o->id() << " " << o->tile()->position().x() << " " << o->tile()->position().y() << "\n";
		}
	}
}

void Console::printTowns() 
{
	for (Object *o : GameManager::get()->objects_) {
		if (o->type() == ObjectType::Town) {
			in() << o->name() << " " << o->id() << " " << o->tile()->position().x() << " " << o->tile()->position().y() << "\n";
		}
	}
}

Player *Console::playerFromName(const QString &name)
{
	for (Player *player :GameManager::get()->players())
	if (player->name() == name) {
		return player;
	}
	return nullptr;
}


Tile *Console::tileFromPos(const QString &first, const QString &second)
{
	QPair<uint, uint> coord = qMakePair(first.toUInt(), second.toUInt());
	if (coord.first && coord.second) {
		return GameManager::get()->board_->getTile(coord.first, coord.second);
	}
	return nullptr;
}

Object *Console::ObjectFromUID(const QString &s)
{
	UID id = s.toUInt();
	if (id) {
		return GameManager::get()->objectP(id);
	}
	return nullptr;
}

Unit *Console::unitFromPos(const QString &first, const QString &second)
{
	QPair<uint, uint> coord = qMakePair(first.toUInt(), second.toUInt());
		if (coord.first && coord.second) {
		return GameManager::get()->board_->getTile(coord.first, coord.second)->unit();
	}
	return nullptr;
}

Town *Console::townFromPos(const QString &first, const QString &second)
{
	QPair<uint, uint> coord = qMakePair(first.toUInt(), second.toUInt());
		if (coord.first && coord.second) {
		return GameManager::get()->board_->getTile(coord.first, coord.second)->town();
	}
	return nullptr;
}

bool Console::parse(const QString &input)
{
	addToHistory(input);
	in() << input << "\n";
	Action *action = parseInput(input);
	if (action == nullptr) {
		return parseCommand(input);
	}
	
	return action->perform();
}
