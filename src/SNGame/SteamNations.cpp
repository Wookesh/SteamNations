#include "SteamNations.hpp"
#include <QHBoxLayout>
#include "MenuController.hpp"
#include "GraphicInterface.h"

SteamNations::SteamNations(QWidget *parent) : QMainWindow(parent)
{
	createMenus();
}

SteamNations::~SteamNations()
{}


void SteamNations::createMenus()
{
	widgets_ = new QStackedWidget(this);
	QWidget *placeholder = new QWidget(this);
	
	QHBoxLayout *layout = new QHBoxLayout();
	
	MenuController *menuController = new MenuController(this);
	
	GraphicInterface *gi = new GraphicInterface(this);
	widgets_->addWidget(gi);
	connect(menuController, &MenuController::setView, [this, gi](){widgets_->setCurrentWidget(gi);});
	layout->addStretch(); //REMOVELATER
	layout->addWidget(menuController);
	layout->addStretch(); //REMOVELATER
	placeholder->setLayout(layout);
	widgets_->addWidget(placeholder);
	widgets_->setCurrentWidget(placeholder);
	setCentralWidget(widgets_);
}
