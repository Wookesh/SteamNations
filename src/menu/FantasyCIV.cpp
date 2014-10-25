#include "FantasyCIV.hpp"
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QApplication>

FantasyCIV::FantasyCIV(QWidget *parent) : QMainWindow(parent), buildVersion_(1)
{
	statusBar()->showMessage("Build v" + QString::number(buildVersion_));
	createMenus();
}

FantasyCIV::~FantasyCIV()
{}


void FantasyCIV::createMenus()
{
	menus_ = new QStackedWidget(this);
	QWidget *placeholder = new QWidget(this);
	
	QHBoxLayout *layout = new QHBoxLayout();
	
	MainMenu *mainMenu = new MainMenu(this);
	layout->addStretch(); //REMOVELATER
	layout->addWidget(mainMenu);
	layout->addStretch(); //REMOVELATER
	placeholder->setLayout(layout);
	menus_->addWidget(placeholder);
	menus_->setCurrentWidget(placeholder);
	setCentralWidget(menus_);
}

//--------------------- MainMenu --------------------------//


MainMenu::MainMenu(QWidget* parent): QWidget(parent)
{
	createLayout();
}

MainMenu::~MainMenu()
{}

void MainMenu::createLayout()
{
	QVBoxLayout *layout = new QVBoxLayout();
	
	QPushButton *newGameButton = new QPushButton("New Game");
	connect(newGameButton, &QPushButton::clicked, this, &MainMenu::newGame);
	layout->addWidget(newGameButton);
	
	QPushButton *loadGameButton = new QPushButton("Load Game");
	connect(loadGameButton, &QPushButton::clicked, this, &MainMenu::loadGame);
	layout->addWidget(loadGameButton);
	
	QPushButton *optionsButton = new  QPushButton("Options");
	connect(optionsButton, &QPushButton::clicked, this, &MainMenu::options);
	layout->addWidget(optionsButton);
	
	QPushButton *exitButton = new QPushButton("Exit");
	connect(exitButton, &QPushButton::clicked, qApp, &QApplication::exit);
	layout->addWidget(exitButton);
	
	setLayout(layout);
}


//--------------------- PlayMenu --------------------------//


PlayMenu::PlayMenu(QWidget* parent): QWidget(parent)
{

}

PlayMenu::~PlayMenu()
{

}


//--------------------- OptionsMenu ------------------------//


OptionsMenu::OptionsMenu(QWidget* parent): QWidget(parent)
{

}

OptionsMenu::~OptionsMenu()
{

}

