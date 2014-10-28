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
	QVBoxLayout *layout = new QVBoxLayout();
	QList<QPair<QString, void (MainMenu::*)()>> list({ qMakePair(QString("New Game"), &MainMenu::newGame),
																		qMakePair(QString("Load Game"), &MainMenu::loadGame),
																		qMakePair(QString("Options"), &MainMenu::options),
																		qMakePair(QString("Exit"), &MainMenu::exit)});
	
	for (QPair<QString, void (MainMenu::*)()> p: list) {
		QPushButton *b = new QPushButton(p.first);
		connect(b, &QPushButton::clicked, this, p.second);
		layout->addWidget(b);
	}
	
	setLayout(layout);
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
	QVBoxLayout *layout = new QVBoxLayout();
	QList<QPair<QString, void (PlayMenu::*)()>> list({ qMakePair(QString("Back"), &PlayMenu::back)});
	
	for (QPair<QString, void (PlayMenu::*)()> p: list) {
		QPushButton *b = new QPushButton(p.first);
		connect(b, &QPushButton::clicked, this, p.second);
		layout->addWidget(b);
	}
	
	setLayout(layout);
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
	QVBoxLayout *layout = new QVBoxLayout();
	QList<QPair<QString, void (OptionsMenu::*)()>> list({ qMakePair(QString("Back"), &OptionsMenu::back)});
	
	for (QPair<QString, void (OptionsMenu::*)()> p: list) {
		QPushButton *b = new QPushButton(p.first);
		connect(b, &QPushButton::clicked, this, p.second);
		layout->addWidget(b);
	}
	
	setLayout(layout);
}

