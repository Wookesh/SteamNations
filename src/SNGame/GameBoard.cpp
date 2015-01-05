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
	initTimer();
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
	static QSGTexture *artilleryTexture_ = window()->createTextureFromImage(artillery->toImage());
	static QPixmap *heavy = new QPixmap(":images/units/tank.png");
	static QSGTexture *heavyTexture_ = window()->createTextureFromImage(heavy->toImage());
	static QPixmap *infantry = new QPixmap(":images/units/infantry.png");
	static QSGTexture *infantryTexture_ = window()->createTextureFromImage(infantry->toImage());
	static QPixmap *settler = new QPixmap(":images/units/settler.png");
	static QSGTexture *settlerTexture_ = window()->createTextureFromImage(settler->toImage());
	static QPixmap *town = new QPixmap(":images/town.png");
	static QSGTexture *townTexture_ = window()->createTextureFromImage(town->toImage());
	QSGNode *node = mainNode;
	if (!node) {
		
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
				//TODO tymczasowe, póki nie ma typu tile-a
				if(tile->resource() == Resource::Gold)
					hexTexture_ = pustyniaTexture_;
				if(tile->resource() == Resource::Research)
					hexTexture_ = snowTexture_;
				if(tile->resource() == Resource::Food)
					hexTexture_ = fieldTexture_;
				child->setTexture(hexTexture_);
				node->appendChildNode(child);
			}
		}
	} else {
		
		for(int i = 0; i < 50; i++) {
			for(int j = 0; j < 50; j++) {
 				QPointF pos = coordToPos(i, j);
				QSGNode *child = nodeMap[index(i, j)]->node();
				Tile *tile = GameManager::get()->board()->getTile(i,j);
				child->removeAllChildNodes();
				if(tile->town()) {
					QSGSimpleTextureNode *townNode = new QSGSimpleTextureNode();
					QPixmap *townPM = town;
					townNode->setRect(pos.x()-townPM->width() / 2, pos.y() - townPM->height() / 2, townPM->width(), townPM->height());
					
					QSGTexture *texture_ = townTexture_;
					townNode->setTexture(texture_);
					child->appendChildNode(townNode);
				}
				if(tile->unit()) {
					
					QSGSimpleTextureNode *unit = new QSGSimpleTextureNode();
					QPixmap *unitPixMap;
					QSGTexture *texture_;
					if(tile->unit()->pType() == PrototypeType::Infantry) {
						unitPixMap = infantry;
						texture_ = infantryTexture_;
					}
					if(tile->unit()->pType() == PrototypeType::Artillery) {
						unitPixMap = artillery;
						texture_ = artilleryTexture_;
					}
					if(tile->unit()->pType() == PrototypeType::Heavy) {
						unitPixMap = heavy;
						texture_ = heavyTexture_;
					}
					if(tile->unit()->pType() == PrototypeType::Settler) {
						unitPixMap = settler;
						texture_ = settlerTexture_;
					}
					unit->setRect(pos.x()-unitPixMap->width() / 2, pos.y() - unitPixMap->height() / 2, unitPixMap->width(), unitPixMap->height());
					unit->setTexture(texture_);
					child->appendChildNode(unit);
				}
			}
		}
	}
	
	return node;
}
