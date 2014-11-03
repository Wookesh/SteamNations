#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include <QStackedWidget>
#include "Menus.hpp"

class MenuController : public QStackedWidget {
Q_OBJECT
public:
	MenuController(QWidget *parent = nullptr);
	~MenuController();
private:
	MainMenu *mainMenu_;
	PlayMenu *playMenu_;
	OptionsMenu *optionsMenu_;
signals:
	void setView();
};

#endif
