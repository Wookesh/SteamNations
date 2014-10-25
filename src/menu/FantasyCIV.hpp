#ifndef FANTASYCIV_HPP
#define FANTASYCIV_HPP

#include <QMainWindow>
#include <QStackedWidget>

class FantasyCIV : public QMainWindow {
Q_OBJECT
public:
	FantasyCIV(QWidget *parent = nullptr);
	virtual ~FantasyCIV();
private:
	int buildVersion_;
	QStackedWidget *menus_;
	
	
	void createMenus();
};


/*
 * MainMenu
 */

class MainMenu : public QWidget {
Q_OBJECT
public:
	MainMenu(QWidget *parent = nullptr);
	virtual ~MainMenu();
private:
	void createLayout();
signals:
	void newGame();
	void loadGame();
	void options();
};


/*
 * PlayMenu
 */

class PlayMenu : public QWidget {
Q_OBJECT
public :
	PlayMenu(QWidget *parent = nullptr);
	virtual ~PlayMenu();
};

/*
 * OptionsMenu
 */

class OptionsMenu : public QWidget {
Q_OBJECT
public :
	OptionsMenu(QWidget *parent = nullptr);
	virtual ~OptionsMenu();
};

#endif
