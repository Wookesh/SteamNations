#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <QObject>

class GameManager : public QObject {
Q_OBJECT
public:
	GameManager(QObject *parent = nullptr);
	~GameManager();
private:
};

#endif