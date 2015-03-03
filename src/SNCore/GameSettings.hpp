#ifndef GAME_SETTINGS_HPP
#define GAME_SETTINGS_HPP

#include <QtGlobal>
#include <QSize>
#include <QVector>
#include <QString>
#include <QObject>
#include <QPair>
#include <QtGui/QColor>

class GameSettings : public QObject {
Q_OBJECT
public:
	Q_PROPERTY(int playersCount READ playersCount WRITE setPlayersCount)
	Q_PROPERTY(QSize boardSize READ boardSize WRITE setBoardSize)
	
	int playersCount() const;
	void setPlayersCount(int playersCount);
	
	QSize boardSize() const;
	void setBoardSize(QSize boardSize);
	
	QString playerName(int index) const;
	void setPlayerName(int index, const QString &name);
	QVector<QString> playerNames() const;
	
	QColor playerColor(int index) const;
	void setPlayerColor(int index, QColor color);
	
	bool validate() const;
	QVector<QPair<QString, QColor>> playerData() const;
private:
	int playersCount_;
	QSize boardSize_;
	QVector<QString> playerNames_;
	
	QVector<QColor> playerColors_;
};


#endif