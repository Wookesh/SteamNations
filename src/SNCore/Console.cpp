#include "Console.hpp"

Console::Console(const QObject *parent): QObject(parent)
{

}

void Console::start()
{
	
}

bool Console::parseInput(const QString &input)
{
	QStringList splittedInput = input.split(" ");
	QString command = splittedInput.first();
	
	if (!commands_.contains(command))
		return false;
	
	ActionType actionType = commands_[command];
}
