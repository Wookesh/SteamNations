#include <QPainter>
#include <QDebug>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <QTimer>
#include <QDebug>
#include "../SNCore/GameManager.hpp"
#include "../SNCore/Board.hpp"
#include "../SNCore/Tile.hpp"
#include "../SNCore/Objects/Town.hpp"
#include "../SNCore/Objects/Unit.hpp"
#include "GameBoard.hpp"
#include "BoardField.hpp"

QTimer *GameBoard::timer_ = nullptr;

void GameBoard::initTimer()
{
	if (timer_ == nullptr) {
		timer_ = new QTimer();
		timer_->setInterval(250);
		timer_->start();
	}
	connect(timer_, &QTimer::timeout, this, &GameBoard::nextFrame);
}

void GameBoard::nextFrame()
{
	qDebug() << "update";

	update();

}

GameBoard::GameBoard(QQuickItem *parent)
	: QQuickItem(parent)
{
	setFlag(QQuickItem::ItemHasContents, true);
	initTimer();
	GameManager::init();
	GameManager::get()->setBoard(new Board(30, 30));
	GameManager::get()->initGame();
}

int GameBoard::index(int x, int y)
{
	return x + y * 30;
}

QSGNode *GameBoard::updatePaintNode(QSGNode *mainNode, UpdatePaintNodeData *)
{
	QSGNode *node = mainNode;
	if (!node) {
		node = new QSGNode();
		for(int i = 0; i < 30; i++) {
			for(int j = 0; j < 30; j++) {
				QSGGeometryNode *child = new QSGGeometryNode();
				
				nodeMap[index(i, j)] = new BoardField(child, GameManager::get()->board()->getTile(i,j));
				
				QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 6);
				geometry->setDrawingMode(GL_POLYGON);
				geometry->setLineWidth(3);
				int addX, addY;
				addX = 48 * i;
				addY = i%2 ? 56 * j : 56 * j + 28;

				geometry->vertexDataAsPoint2D()[0].set(16 + addX, 0 + addY);
				geometry->vertexDataAsPoint2D()[1].set(48 + addX, 0 + addY);
				geometry->vertexDataAsPoint2D()[2].set(64 + addX, 28 + addY);
				geometry->vertexDataAsPoint2D()[3].set(48 + addX, 56 + addY);
				geometry->vertexDataAsPoint2D()[4].set(16 + addX, 56 + addY);
				geometry->vertexDataAsPoint2D()[5].set(0 + addX, 28 + addY);
				QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
				BoardField *bf = nodeMap[index(i,j)];
				
				material->setColor(bf->tileColor());

				child->setGeometry(geometry);
				child->setFlag(QSGNode::OwnsGeometry);
				child->setMaterial(material);
				child->setFlag(QSGNode::OwnsMaterial);
				node->appendChildNode(child);
			}
		}
	}
	return node;
}
