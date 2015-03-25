#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <QObject>
#include <QStringList>
#include <QSet>
#include <QTextStream>
#include <QThread>
#include <QBuffer>
#include <QTimer>

#include "Actions/Action.hpp"

class Player;
class Unit;
class Town;
class Tile;
class Object;
class Console : public QObject {
Q_OBJECT
public:
	Q_PROPERTY(QStringList history READ history NOTIFY historyChanged)
	Q_PROPERTY(QStringList log READ log NOTIFY logChanged)
	Console(QObject *parent = nullptr);
	virtual ~Console();
	const QStringList &history();
	const QStringList &log();
	
	QTextStream &in();
private:
	Action *parseInput(const QString &input);
	bool parseCommand(const QString &input);
	Object *ObjectFromUID(const QString &s);
	Town *townFromPos(const QString &first, const QString &second);
	Unit *unitFromPos(const QString &first, const QString &second);
	Tile *tileFromPos(const QString &first, const QString &second);
	Player *playerFromName(const QString &name);
	bool isCommandACheat(const QString &command);
	void addToHistory(const QString &input);
	void addToLog(const QString &string);
	QStringList history_;
	QStringList log_;
	QTextStream io_;
	QString stringBuf_;
	QTimer *flushingTimer_;
	static const QSet<QString> commands();
	
	void printUnits();
	void printTowns();
	void save();
	static const int FLUSHTIME = 100;
public slots:
	void read();
	bool parse(const QString &input);
private slots:
	void flushStream();
signals:
	void historyChanged();
	void logChanged();
};

#endif
