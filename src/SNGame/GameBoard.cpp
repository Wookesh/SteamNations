#include <QPainter>
#include <QDebug>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <QTimer>
#include <QPixmap>

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
	GameManager::get()->setBoard(new Board(50, 50));
	GameManager::get()->initGame();
}

int GameBoard::index(int x, int y)
{
	return x + y * 50;
}

QSGNode *GameBoard::updatePaintNode(QSGNode *mainNode, UpdatePaintNodeData *)
{
	QSGNode *node = mainNode;
	if (!node) {
		//TODO trzeba to potem przerobić na imageManagera
		static QPixmap *pustynia = new QPixmap(":images/hexes/pustynia.png");
		static QSGTexture *pustyniaTexture_ = window()->createTextureFromImage(pustynia->toImage());
		static QPixmap *snow = new QPixmap(":images/hexes/snow1.png");
		static QSGTexture *snowTexture_ = window()->createTextureFromImage(snow->toImage());
		static QPixmap *field = new QPixmap(":images/hexes/field.png");
		static QSGTexture *fieldTexture_ = window()->createTextureFromImage(field->toImage());
		static QPixmap *ruins = new QPixmap(":images/hexes/ruiny1.png");
		static QSGTexture *ruinsTexture_ = window()->createTextureFromImage(ruins->toImage());
		static QPixmap *artillery = new QPixmap(":images/units/artilery.png");
		static QPixmap *heavy = new QPixmap(":images/units/tank.png");
		static QPixmap *infantry = new QPixmap(":images/units/infantry.png");
		static QPixmap *settler = new QPixmap(":images/units/settler.png");
		node = new QSGNode();
		for(int i = 0; i < 50; i++) {
			for(int j = 0; j < 50; j++) {
				Tile *tile = GameManager::get()->board()->getTile(i,j);
				QSGSimpleTextureNode *child = new QSGSimpleTextureNode();
				nodeMap[index(i, j)] = new BoardField(child, tile);
				
 				QPointF pos = coordToPos(i, j);
				
				
					QPixmap *hexPixMap = pustynia;
					child->setRect(pos.x()-hexPixMap->width() / 2, pos.y() - hexPixMap->height() / 2, hexPixMap->width(), hexPixMap->height());
					QSGTexture *hexTexture_ = ruinsTexture_;
					if(tile->resource() == Resource::Gold)
						hexTexture_ = pustyniaTexture_;
					if(tile->resource() == Resource::Research)
						hexTexture_ = snowTexture_;
					if(tile->resource() == Resource::Food)
						hexTexture_ = fieldTexture_;
					child->setTexture(hexTexture_);
// 				QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 6);
// 				geometry->setDrawingMode(GL_POLYGON);
// 				geometry->setLineWidth(3);
// 				
// 				for (int i = 0; i < 6; ++i)
// 					geometry->vertexDataAsPoint2D()[i].set(
// 						BoardField::SIZE * qCos(2 * M_PI / 6 * i) + pos.x(),
// 						BoardField::SIZE * qSin(2 * M_PI / 6 * i) + pos.y());
// 				
// 				QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
// 				BoardField *bf = nodeMap[index(i,j)];
// 				
// 				material->setColor(bf->tileColor());
// 
// 				child->setGeometry(geometry);
// 				child->setFlag(QSGNode::OwnsGeometry);
// 				child->setMaterial(material);
// 				child->setFlag(QSGNode::OwnsMaterial);
				node->appendChildNode(child);
				if(tile->unit()) {
					QSGSimpleTextureNode *unit = new QSGSimpleTextureNode();
					QPixmap *unitPixMap;
					if(tile->unit()->pType() == PrototypeType::Infantry)
						unitPixMap = infantry;
					if(tile->unit()->pType() == PrototypeType::Artillery)
						unitPixMap = artillery;
					if(tile->unit()->pType() == PrototypeType::Heavy)
						unitPixMap = heavy;
					if(tile->unit()->pType() == PrototypeType::Settler)
						unitPixMap = settler;
					unit->setRect(pos.x()-unitPixMap->width() / 2, pos.y() - unitPixMap->height() / 2, unitPixMap->width(), unitPixMap->height());
					QSGTexture *texture_ = window()->createTextureFromImage(unitPixMap->toImage());
					unit->setTexture(texture_);
					child->appendChildNode(unit);
				}
			}
		}
	}
	return node;
}
