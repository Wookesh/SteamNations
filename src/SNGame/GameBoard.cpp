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
#include "TextureManager.hpp"

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
	: QQuickItem(parent), textureManager_(new TextureManager(this))
{
	setFlag(QQuickItem::ItemHasContents, true);
	setAntialiasing(true);
	initTimer();
	GameManager::init();
	GameManager::get()->setBoard(new Board(50, 50));
	GameManager::get()->initGame();
	//connect(this, &GameBoard::windowChanged, imageManager_, &ImageManager::loadTextures);
}

int GameBoard::index(int x, int y)
{
	return x + y * 50;
}

QSGNode *GameBoard::updatePaintNode(QSGNode *mainNode, UpdatePaintNodeData *)
{
	if (!textureManager_->isLoaded())
		textureManager_->loadTextures(window());

	QSGNode *node = mainNode;
	if (!node) {
		
		node = new QSGNode();
		for(int i = 0; i < 50; i++) {
			for(int j = 0; j < 50; j++) {
				Tile *tile = GameManager::get()->board()->getTile(i,j);
				QSGSimpleTextureNode *child = new QSGSimpleTextureNode();
				nodeMap[index(i, j)] = new BoardField(child, tile);
				
 				QPointF pos = coordToPos(i, j);
				QSGTexture *hexTexture_ = textureManager_->texture("Tundra");
				//TODO tymczasowe, póki nie ma typu tile-a
				if (tile->resource() == Resource::Gold)
					hexTexture_ = textureManager_->texture("Hill");
				if (tile->resource() == Resource::Research)
					hexTexture_ = textureManager_->texture("Ruins2");
				if (tile->resource() == Resource::Food)
					hexTexture_ = textureManager_->texture("Field");
				child->setTexture(hexTexture_);
				child->setRect(pos.x()-hexTexture_->textureSize().width() / 2, pos.y() - hexTexture_->textureSize().height() / 2, hexTexture_->textureSize().width(), hexTexture_->textureSize().height());
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
				if (tile->town()) {
					QSGSimpleTextureNode *townNode = new QSGSimpleTextureNode();
					QSGTexture *texture_ = textureManager_->texture("Town");
					townNode->setTexture(texture_);
					townNode->setRect(pos.x()-texture_->textureSize().width() / 2, pos.y() - texture_->textureSize().height() / 2, texture_->textureSize().width(), texture_->textureSize().height());
					child->appendChildNode(townNode);
				}
				if (tile->unit()) {
					
					QSGSimpleTextureNode *unit = new QSGSimpleTextureNode();
					QSGTexture *texture_= textureManager_->texture((QString)(tile->unit()->pType()));
					
					if (texture_ == nullptr)
						qDebug() << "[ERROR] texture is null";
					unit->setRect(pos.x()-texture_->textureSize().width() / 2, pos.y() - texture_->textureSize().height() / 2, texture_->textureSize().width(), texture_->textureSize().height());
					unit->setTexture(texture_);
					child->appendChildNode(unit);
				}
			}
		}
	}
	
	return node;
}


void GameBoard::click(int mouseX, int mouseY, int x, int y, float scale)
{
	//qDebug() << "mouse: " << mouseX << " " << mouseY << " scene: " << x << " " << y << " scale: " << scale;
}
