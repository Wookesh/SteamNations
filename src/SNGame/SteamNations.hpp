#ifndef STEAM_NATIONS_HPP
#define STEAM_NATIONS_HPP

#include <QMainWindow>
#include <QStackedWidget>

class SteamNations : public QMainWindow {
Q_OBJECT
public:
	SteamNations(QWidget *parent = nullptr);
	virtual ~SteamNations();
private:
	QStackedWidget *widgets_;
	
	void createMenus();
};

#endif