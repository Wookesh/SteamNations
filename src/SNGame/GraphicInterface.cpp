#include "GraphicInterface.hpp"
#include "../SNCore/GameManager.hpp"
#include <QVBoxLayout>
#include <QApplication>

GraphicInterface::GraphicInterface(QWidget *parent) : QWidget(parent)
{
	GameManager::init();
	GameManager::get()->setBoard(new Board(50, 50));
	connect(GameManager::get(), &GameManager::gameEnded, [this](){gameView_->setInteractive(false);});
	scene_ = new SNScene(GameManager::get(), this);
	gameView_ = new GameView(this);
	gameView_->setScene(scene_);
	createInterface();
}

GraphicInterface::~GraphicInterface()
{
	GameManager::clean();
}

void GraphicInterface::createInterface()
{
	exitButton_ = new QPushButton("Exit", gameView_);
	connect(exitButton_, &QPushButton::clicked, qApp, &QApplication::exit);
	nextTurn_ = new NextTurnButton(gameView_);
	connect(nextTurn_, &NextTurnButton::clicked, GameManager::get(), &GameManager::endTurn);
	infobox_ = new ObjectInfoBox(gameView_);
	connect(scene_, &SNScene::selectionUpdate, this, &GraphicInterface::displayInfo);
	connect(scene_, &SNScene::noSelection, infobox_, &ObjectInfoBox::hide);
}

void GraphicInterface::displayInfo()
{
	if (!infobox_->isVisible())
		infobox_->setVisible(true);
	infobox_->setObject(scene_->selectedObject(), scene_->objectActions());
}

void GraphicInterface::resizeEvent(QResizeEvent *event)
{
	exitButton_->move(0,0);
	gameView_->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
	nextTurn_->move(0, event->size().height() - nextTurn_->sizeHint().height());
	infobox_->move(event->size().width() - infobox_->sizeHint().width(), 0);
	QWidget::resizeEvent(event);
}
