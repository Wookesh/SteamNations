#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <QObject>
#include <QStringList>
#include <QHash>
#include <Actions/Action.hpp>

class Console : public QObject {
public:
	Console(const QObject *parent);
	void start();
private:
	Action *parseInput(const QString &input);
	bool isCommandACheat(const QString &command);
	QStringList history_;
	QHash<QString, ActionType> commands_;
};


#endif