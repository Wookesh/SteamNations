#include "GraphicInterface.h"
#include <QVBoxLayout>

GraphicInterface::GraphicInterface(QWidget *parent) : QWidget(parent)
{
	GameManager::init();
	gameManager_ = GameManager::get();
	gameManager_->setBoard(new Board(50, 50));
	scene_ = new SNScene(gameManager_, this);
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
