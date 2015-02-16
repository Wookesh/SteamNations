#include "GameSettings.hpp"

bool GameSettings::validate() const 
{
	if (playerNames.size() != playersCount || playerColors.size() != playersCount)
		return false;
	
	if (playersCount < 1 || playersCount > 4)
		return false;
	
	if (boardSize.width() < 10 || boardSize.width() > 50)
		return false;
	
	if (boardSize.height() < 10 || boardSize.height() > 50)
		return false;
	
	for (QString name : playerNames)
		if (name.isEmpty())
			return false;
	return true;
}

QVector<QPair<QString, Qt::GlobalColor>> GameSettings::playerData() const 
{
	QVector<QPair<QString, Qt::GlobalColor>> ret(playersCount);
	for (int i = 0; i < playersCount; ++i)
		ret.push_back(qMakePair(playerNames[i], playerColors[i]));
	return ret;
}