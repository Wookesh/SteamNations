#include "GraphicInterface.h"
#include <QVBoxLayout>

GraphicInterface::GraphicInterface(QWidget *parent) : QWidget(parent)
{
	GameManager::init();
	gameManager_ = GameManager::get();
	gameView_ = new GameView(this);
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(gameView_);
	layout->setMargin(0);
	setLayout(layout);
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
