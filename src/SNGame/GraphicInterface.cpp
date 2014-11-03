#include "GraphicInterface.h"
#include <QVBoxLayout>
#include <QPushButton>

GraphicInterface::GraphicInterface(QWidget *parent) : QWidget(parent)
{
	gameView_ = new GameView(this);
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(gameView_);
	layout->setMargin(0);
	setLayout(layout);
	testButton_ = new QPushButton(gameView_);
}

GraphicInterface::~GraphicInterface()
{
	
}

void GraphicInterface::resizeEvent(QResizeEvent *event)
{
	gameView_->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
	testButton_->setGeometry(QRect(event->size().width() - 100, event->size().height() - 100, 100, 100));
	QWidget::resizeEvent(event);
}
