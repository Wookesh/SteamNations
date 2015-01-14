#include <QPainter>
#include <QDebug>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <QTimer>

#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/Objects/Town.hpp"
#include "SNCore/Objects/Unit.hpp"
#include "SNHelpers.hpp"
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
	update();
}

GameBoard::GameBoard(QQuickItem *parent)
	: QQuickItem(parent)
{
	setFlag(QQuickItem::ItemHasContents, true);
	setAntialiasing(true);
	//initTimer();
	GameManager::init();
	GameManager::get()->initGame(50, 50);
}

int GameBoard::index(int x, int y)
{
	return x + y * 50;
}

QSGNode *GameBoard::updatePaintNode(QSGNode *mainNode, UpdatePaintNodeData *)
{
	QSGNode *node = mainNode;
	if (!node) {
		node = new QSGNode();
		for(int i = 0; i < 50; i++) {
			for(int j = 0; j < 50; j++) {
				QSGGeometryNode *child = new QSGGeometryNode();
				
				nodeMap[index(i, j)] = new BoardField(child, GameManager::get()->board()->getTile(i,j));
				
				QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 6);
				geometry->setDrawingMode(GL_POLYGON);
				geometry->setLineWidth(3);
				QPointF pos = coordToPos(i, j);
				
				for (int i = 0; i < 6; ++i)
					geometry->vertexDataAsPoint2D()[i].set(
						BoardField::SIZE * qCos(2 * M_PI / 6 * i) + pos.x(),
						BoardField::SIZE * qSin(2 * M_PI / 6 * i) + pos.y());
				
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
