#include "Menus.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPair>
#include <QList>

Menu::Menu(QWidget *parent): QWidget(parent)
{
}

Menu::~Menu()
{

}


//--------------------- MainMenu --------------------------//


MainMenu::MainMenu(QWidget *parent): Menu(parent)
{
	createLayout();
}

MainMenu::~MainMenu()
{}

void MainMenu::createLayout()
{
	QList<QPair<QString, void (MainMenu::*)()>> list({ qMakePair(QString("New Game"), &MainMenu::newGame),
																		qMakePair(QString("Load Game"), &MainMenu::loadGame),
																		qMakePair(QString("Options"), &MainMenu::options),
																		qMakePair(QString("Exit"), &MainMenu::exit)});
	
	setButtons<MainMenu>(list, this);
}


//--------------------- PlayMenu --------------------------//


PlayMenu::PlayMenu(QWidget* parent): Menu(parent)
{
	createLayout();
}

PlayMenu::~PlayMenu()
{

}

void PlayMenu::createLayout()
{
	QList<QPair<QString, void (PlayMenu::*)()>> list({ qMakePair(QString("Back"), &PlayMenu::back)});
	setButtons<PlayMenu>(list, this);
}


//--------------------- OptionsMenu ------------------------//


OptionsMenu::OptionsMenu(QWidget* parent): Menu(parent)
{
	createLayout();
}

OptionsMenu::~OptionsMenu()
{

}

void OptionsMenu::createLayout()
{
	QList<QPair<QString, void (OptionsMenu::*)()>> list({ qMakePair(QString("Back"), &OptionsMenu::back)});
	setButtons<OptionsMenu>(list, this);
}

