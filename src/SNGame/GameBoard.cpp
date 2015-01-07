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
	int x2 = (mouseX - x - (1-scale)*5960/2)/scale;
	int y2 = (mouseY - y -(1-scale)*6920/2)/scale;
	
	double q = 2./3 * (x2+80) / 80;
	double r = (-1./3 * (x2+80) + 1./3*sqrt(3) * (y2+70)) / 80;
	QPointF prob(x2,y2);
	QPoint p[4];
	//qDebug() << "q: " << q << " r: " << r;
	p[0] = QPoint(floor(q), floor(r));
	p[1] = QPoint(ceil(q), ceil(r));
	p[2] = QPoint(floor(q), ceil(r));
	p[3] = QPoint(ceil(q), floor(r));double missmatch = 1000;
	int whichONe = -1;
	for (int i = 0; i < 4; i++) {
		Tile *tile = GameManager::get()->board()->getTileAxial(p[i].x(), p[i].y());
		if(tile) {
			QPointF tmp =coordToPos(tile->position());
			//qDebug() << "tmp: " << tmp << " prob: " << prob;
			tmp -= prob;
			//qDebug() << "= "<< tmp;
			if(sqrt(tmp.x()*tmp.x() + tmp.y()*tmp.y()) < missmatch) {
				missmatch = sqrt(tmp.x()*tmp.x() + tmp.y()*tmp.y());
				whichONe = i;
			}
		}
	}
	
	//qDebug() << "not good " <<whichONe ;
	qDebug() << "good point: "<< GameManager::get()->board()->getTileAxial(p[whichONe].x(), p[whichONe].y())->position();
}
