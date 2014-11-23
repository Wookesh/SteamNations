#include "GraphicInterface.hpp"
#include "../SNCore/GameManager.hpp"
#include "../SNCore/Player.hpp"
#include <QVBoxLayout>
#include <QApplication>
#include <QMessageBox>

GraphicInterface::GraphicInterface(QWidget *parent) : QWidget(parent)
{
	GameManager::init();
	GameManager::get()->setBoard(new Board(50, 50));
	GameManager::get()->initGame();
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
	connect(GameManager::get(), &GameManager::gameEnded, this, &GraphicInterface::displayEndMessage);
	
	exitButton_ = new QPushButton("Exit", gameView_);
	connect(exitButton_, &QPushButton::clicked, qApp, &QApplication::exit);
	nextTurn_ = new NextTurnButton(gameView_);
	connect(nextTurn_, &NextTurnButton::clicked, GameManager::get(), &GameManager::endTurn);
	connect(nextTurn_, &NextTurnButton::clicked, scene_, &SNScene::clearSelect);
// 	connect(nextTurn_, &NextTurnButton::clicked, [this](){gameView_->setInteractive(false);});
// 	connect(GameManager::get(), &GameManager::turnReady, [this](){gameView_->setInteractive(true);});
	infobox_ = new ObjectInfoBox(gameView_);
	connect(scene_, &SNScene::selectionUpdate, this, &GraphicInterface::displayInfo);
	connect(scene_, &SNScene::noSelection, infobox_, &ObjectInfoBox::hide);
	connect(infobox_, &ObjectInfoBox::actionPerformed, scene_, &SNScene::clearSelect);
}

void GraphicInterface::displayEndMessage(const Player *player)
{
	QMessageBox *end = new QMessageBox();
	end->addButton("Ok", QMessageBox::AcceptRole);
	end->setText(player == GameManager::get()->currentPlayer() ? "You Won! :D" : "You Lost! :(");
	end->exec();
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
