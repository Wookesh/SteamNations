#include "GameSettings.hpp"



int GameSettings::playersCount() const
{
	return playersCount_;
}

void GameSettings::setPlayersCount(int playersCount)
{
	playersCount_ = playersCount;
}

QSize GameSettings::boardSize() const
{
	return boardSize_;
}

void GameSettings::setBoardSize(QSize boardSize)
{
	boardSize_ = boardSize;
}

QString GameSettings::playerName(int index) const
{
	return playerNames_[index];
}

void GameSettings::setPlayerName(int index, const QString &name)
{
	playerNames_[index] = name;
}

QVector< QString > GameSettings::playerNames() const
{
	return playerNames_;
}


QColor GameSettings::playerColor(int index) const
{
	return playerColors_[index];
}

void GameSettings::setPlayerColor(int index, QColor color)
{
	playerColors_[index] = color;
}

bool GameSettings::validate() const
{
	if (playerNames_.size() != playersCount_ || playerColors_.size() != playersCount_)
		return false;
	
	if (playersCount_ < 2 || playersCount_ > 4)
		return false;
	
	if (boardSize_.width() < 10 || boardSize_.width() > 50)
		return false;
	
	if (boardSize_.height() < 10 || boardSize_.height() > 50)
		return false;
	
	for (QString name : playerNames_)
		if (name.isEmpty())
			return false;
	return true;
}

QVector<QPair<QString, QColor>> GameSettings::playerData() const 
{
	QVector<QPair<QString, QColor>> ret(playersCount_);
	for (int i = 0; i < playersCount_; ++i)
		ret.push_back(qMakePair(playerNames_[i], playerColors_[i]));
	return ret;
}