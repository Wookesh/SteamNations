#include "GraphicInterface.h"
#include "../SNCore/GameManager.hpp"
#include <QVBoxLayout>

GraphicInterface::GraphicInterface(QWidget *parent) : QWidget(parent)
{
	GameManager::init();
	GameManager::get()->setBoard(new Board(50, 50));
	connect(GameManager::get(), &GameManager::gameEnded, [this](){gameView_->setInteractive(false);});
	scene_ = new SNScene(GameManager::get(), this);
	gameView_ = new GameView(this);
	gameView_->setScene(scene_);
	nextTurn_ = new NextTurnButton(gameView_);
}

GraphicInterface::~GraphicInterface()
{
	GameManager::clean();
}

void GraphicInterface::resizeEvent(QResizeEvent *event)
{
	gameView_->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
	nextTurn_->move(0, event->size().height() - nextTurn_->sizeHint().height());
	QWidget::resizeEvent(event);
}
