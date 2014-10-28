#include "FantasyCIV.hpp"
#include <QStatusBar>
#include <QHBoxLayout>
#include "MenuController.hpp"

FantasyCIV::FantasyCIV(QWidget *parent) : QMainWindow(parent), buildVersion_(1)
{
	statusBar()->showMessage("Build v" + QString::number(buildVersion_));
	createMenus();
}

FantasyCIV::~FantasyCIV()
{}


void FantasyCIV::createMenus()
{
	widgets_ = new QStackedWidget(this);
	QWidget *placeholder = new QWidget(this);
	
	QHBoxLayout *layout = new QHBoxLayout();
	
	MenuController *menuController = new MenuController(this);
	//MainMenu *mainMenu = new MainMenu(this);
	layout->addStretch(); //REMOVELATER
	layout->addWidget(menuController);
	layout->addStretch(); //REMOVELATER
	placeholder->setLayout(layout);
	widgets_->addWidget(placeholder);
	widgets_->setCurrentWidget(placeholder);
	setCentralWidget(widgets_);
}
