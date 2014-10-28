#include "MenuController.hpp"
#include <QApplication>

MenuController::MenuController(QWidget *parent): QStackedWidget(parent)
{
	mainMenu_ = new MainMenu(this);
	connect(mainMenu_, &MainMenu::exit, [](){qApp->exit();});
	connect(mainMenu_, &MainMenu::options, [this](){setCurrentWidget(optionsMenu_);});
	connect(mainMenu_, &MainMenu::newGame, [this](){setCurrentWidget(playMenu_);});
	playMenu_ = new PlayMenu(this);
	connect(playMenu_, &PlayMenu::back, [this](){setCurrentWidget(mainMenu_);});
	optionsMenu_ = new OptionsMenu(this);
	connect(optionsMenu_, &OptionsMenu::back, [this](){setCurrentWidget(mainMenu_);});
	addWidget(mainMenu_);
	addWidget(playMenu_);
	addWidget(optionsMenu_);
	setCurrentWidget(mainMenu_);
}

MenuController::~MenuController()
{
	
}
