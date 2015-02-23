#ifndef GAME_SETTINGS_HPP
#define GAME_SETTINGS_HPP

#include <QtGlobal>
#include <QSize>
#include <QVector>
#include <QString>
#include <QObject>
#include <QPair>

class GameSettings : public QObject {
Q_OBJECT
public:
	quint8 playersCount;
	QSize boardSize;
	QVector<QString> playerNames;
	QVector<Qt::GlobalColor> playerColors;
	
	bool validate() const;
	QVector<QPair<QString, Qt::GlobalColor>> playerData() const;
};


#endif