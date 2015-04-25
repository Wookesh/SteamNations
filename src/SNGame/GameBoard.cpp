#include <QPainter>
#include <QDebug>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <QTimer>
#include <QPixmap>
#include <QDebug>

#include "SNCore/GameManager.hpp"
#include "SNCore/Board.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/Objects/Town.hpp"
#include "SNCore/Objects/Unit.hpp"
#include "SNHelpers.hpp"
#include "GameBoard.hpp"
#include "BoardField.hpp"
#include "TextureManager.hpp"
#include "SNCore/Console.hpp"
#include "SNCore/Objects/Object.hpp"
#include "InfoBox.hpp"
#include "SNCore/Player.hpp"
#include "SNCore/Actions/Actions.hpp"
#include "SNCore/Bonuses/Bonuses.hpp"
#include "SNCore/Resources.hpp"

QTimer *GameBoard::timer_ = nullptr;

void GameBoard::initTimer()
{
	if (timer_ == nullptr) {
		timer_ = new QTimer();
		timer_->setInterval(INTERVAL);
		timer_->start();
	}
	
	connect(timer_, &QTimer::timeout, this, &GameBoard::nextFrame);
	connect(GameManager::get(), &GameManager::turnReady, this, &GameBoard::updateResources);
}

void GameBoard::nextFrame()
{
	update();
}

GameBoard::GameBoard(QQuickItem *parent)
	: QQuickItem(parent), textureManager_(new TextureManager(this)), selectedObject_(nullptr),
	infobox_(new InfoBox()), boardSet_(false)
{
	setFlag(QQuickItem::ItemHasContents, true);
	setAntialiasing(true);
	initTimer();
	connect(GameManager::get(), &GameManager::turnEnded ,this, &GameBoard::clearActions);
	
	BonusManager::init();
	bonusManager_ = BonusManager::get();
}

InfoBox* GameBoard::infobox()
{
	return infobox_;
}


int GameBoard::index(int x, int y)
{
	return x + y * GameManager::get()->board()->width();
}

const QColor GameBoard::highlightColor(ActionType actionType)
{
	static const QHash<ActionType, QColor> map({
		{ActionType::Attack, Qt::red},
		{ActionType::Capture, Qt::magenta},
		{ActionType::Move, Qt::cyan},
		{ActionType::None, Qt::white},
		{ActionType::Settle, Qt::yellow},
		{ActionType::CreateUnit, Qt::darkYellow}
	});
	return map[actionType];
}

const qreal GameBoard::GBcos(int i)
{
	static const QVector<qreal> map = []{
		QVector<qreal> result;
		for (int i = 0; i < 6; ++i)
			result.push_back(qCos(2 * M_PI / 6 * i));
		return result;
	}();
	return map[i];
}

const qreal GameBoard::GBsin(int i)
{
	static const QVector<qreal> map = []{
		QVector<qreal> result;
		for (int i = 0; i < 6; ++i)
			result.push_back(qSin(2 * M_PI / 6 * i));
		return result;
	}();
	return map[i];
}

QSGNode *GameBoard::updatePaintNode(QSGNode *mainNode, UpdatePaintNodeData *)
{
	QSGNode *node = mainNode;
	if (GameManager::get()->board() == nullptr) {
		boardSet_ = false;
		return mainNode;
	}
	
	if (!textureManager_->isLoaded())
		textureManager_->loadTextures(window());
	
	int width = GameManager::get()->board()->width();
	int height = GameManager::get()->board()->height();
	
	if (!boardSet_) {
		boardSet_  = true;
		qDeleteAll(nodeMap.values());
		nodeMap.clear();
		if (mainNode) {
			mainNode->removeAllChildNodes();
			delete mainNode;
		} 
		node = nullptr;
	}
	
	if (!node) {
		node = new QSGNode();
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
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
				child->appendChildNode(new QSGNode());
				node->appendChildNode(child);
			}
		}
		
		emit boardSet();
	} else {
		//FIXME trzeba bardziej dynamicznie zarządzać kiedy usuwamy node'y, szczególnie te z ciniem
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
 				QPointF pos = coordToPos(i, j);
				QSGNode *child = nodeMap[index(i, j)]->node();
				Tile *tile = GameManager::get()->board()->getTile(i,j);
				QSGNode *placeholder = child->firstChild();
				delete placeholder;
				child->appendChildNode(new QSGNode());
				child = child->firstChild();
				
				if (tile->visible(GameManager::get()->currentPlayer())) {
					if (tile->town()) {
						QSGSimpleTextureNode *townShadow = new QSGSimpleTextureNode();
						QSGTexture *texture_= textureManager_->texture("TownShadow");
						
						townShadow->setRect(pos.x()-texture_->textureSize().width() / 2, pos.y() - texture_->textureSize().height() / 2, texture_->textureSize().width(), texture_->textureSize().height());
						townShadow->setTexture(texture_);
						child->appendChildNode(townShadow);
						
						QSGSimpleTextureNode *townNode = new QSGSimpleTextureNode();
						texture_ = textureManager_->texture("Town");
						townNode->setTexture(texture_);
						townNode->setRect(pos.x()-texture_->textureSize().width() / 2, pos.y() - texture_->textureSize().height() / 2, texture_->textureSize().width(), texture_->textureSize().height());
						child->appendChildNode(townNode);
					}
					if (tile->unit()) {
						
						QSGSimpleTextureNode *unitShadow = new QSGSimpleTextureNode();
						QSGTexture *texture_= textureManager_->texture((QString)(tile->unit()->pType())+"Shadow");
						
						if (texture_ == nullptr)
							GMlog() << "[ERROR] texture is null";
						unitShadow->setRect(pos.x()-texture_->textureSize().width() / 2, pos.y() - texture_->textureSize().height() / 2, texture_->textureSize().width(), texture_->textureSize().height());
						unitShadow->setTexture(texture_);
						child->appendChildNode(unitShadow);
						
						QSGSimpleTextureNode *unit = new QSGSimpleTextureNode();
						texture_= textureManager_->texture((QString)(tile->unit()->pType()));
						
						if (texture_ == nullptr)
							GMlog() << "[ERROR] texture is null";
						unit->setRect(pos.x()-texture_->textureSize().width() / 2, pos.y() - texture_->textureSize().height() / 2, texture_->textureSize().width(), texture_->textureSize().height());
						unit->setTexture(texture_);
						child->appendChildNode(unit);
					}
				} else {
					QSGSimpleTextureNode *fogNode = new QSGSimpleTextureNode();
					QSGTexture *texture_ = textureManager_->texture("Fog");
					fogNode->setTexture(texture_);
					fogNode->setRect(pos.x()-texture_->textureSize().width() / 2, pos.y() - texture_->textureSize().height() / 2, texture_->textureSize().width(), texture_->textureSize().height());
					child->appendChildNode(fogNode);
				}
			}
		}
		
					if(selectedObject_) {
						if((selectedObject_->type() == ObjectType::Town) && (selectedObject_->owner() == GameManager::get()->currentPlayer())) {
							const Town *town = static_cast<const Town*>(selectedObject_);
							for(Tile *townTile : town->townTiles()){
									
								QSGNode *child = nodeMap[index(townTile->position().x(), townTile->position().y())]->node();
								child = child->firstChild();
								QSGOpacityNode *opacity = new QSGOpacityNode();
								opacity->setOpacity(SHADOW_OPACITY);
								QSGGeometryNode *shadow = new QSGGeometryNode();
								QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 18);
								geometry->setDrawingMode(GL_TRIANGLES);
								QPointF pos = coordToPos(townTile->position().x(), townTile->position().y());
								
								for (int i = 0; i < 6; ++i) {
									geometry->vertexDataAsPoint2D()[3 * i].set(
										BoardField::SIZE * GBcos(i) + pos.x(),
										BoardField::SIZE * GBsin(i) + pos.y());
									geometry->vertexDataAsPoint2D()[3 * i + 1].set(
										BoardField::SIZE * GBcos((i + 1) % 6) + pos.x(),
										BoardField::SIZE * GBsin((i + 1) % 6) + pos.y());
									geometry->vertexDataAsPoint2D()[3 * i + 2].set(
										pos.x(),
										pos.y());
								}
								
								QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
								material->setColor(Qt::white);
								shadow->setGeometry(geometry);
								shadow->setFlag(QSGNode::OwnsGeometry);
								shadow->setMaterial(material);
								shadow->setFlag(QSGNode::OwnsMaterial);
								child->appendChildNode(opacity);
								opacity->appendChildNode(shadow);
								
							}
						}
					}
		for (Action *action : mapActions_) {
			QSGNode *child = nodeMap[index(action->tile()->position().x(), action->tile()->position().y())]->node();
			child = child->firstChild();
			QSGOpacityNode *opacity = new QSGOpacityNode();
			opacity->setOpacity(SHADOW_OPACITY);
			QSGGeometryNode *shadow = new QSGGeometryNode();
			QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 18);
			geometry->setDrawingMode(GL_TRIANGLES);
			QPointF pos = coordToPos(action->tile()->position().x(), action->tile()->position().y());
			
			for (int i = 0; i < 6; ++i) {
				geometry->vertexDataAsPoint2D()[3 * i].set(
					BoardField::SIZE * GBcos(i) + pos.x(),
					BoardField::SIZE * GBsin(i) + pos.y());
				geometry->vertexDataAsPoint2D()[3 * i + 1].set(
					BoardField::SIZE * GBcos((i + 1) % 6) + pos.x(),
					BoardField::SIZE * GBsin((i + 1) % 6) + pos.y());
				geometry->vertexDataAsPoint2D()[3 * i + 2].set(
					pos.x(),
					pos.y());
			}
			
			QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
			material->setColor(highlightColor(action->type()));
			shadow->setGeometry(geometry);
			shadow->setFlag(QSGNode::OwnsGeometry);
			shadow->setMaterial(material);
			shadow->setFlag(QSGNode::OwnsMaterial);
			child->appendChildNode(opacity);
			opacity->appendChildNode(shadow);
		}
		
	}
	
	return node;
}

QPoint GameBoard::pixelToHex(int x, int y)
{
	int size = BoardField::SIZE;
	double q = 2.0 / 3 * (x + size) / size;
	double r = (-1.0 / 3 * (x + size) + 1.0 / 3 * sqrt(3) * (y + size * sqrt(3) / 2)) / size;
	QPointF prob(x,y);
	QPoint c(qFloor(q), qFloor(r));
	QVector<QPoint> p({
		{c.x(),c.y()}, 
		{c.x(),c.y() + 1}, 
		{c.x(),c.y() - 1}, 
		{c.x() + 1,c.y()}, 
		{c.x() - 1,c.y()}, 
		{c.x() + 1,c.y() - 1}, 
		{c.x() - 1,c.y() + 1}
	});
	double missmatch = std::numeric_limits<double>::max();
	int whichONe;
	int missmatches = 0;
	for (int i = 0; i < p.size(); ++i) {
		Tile *tile = GameManager::get()->board()->getTileAxial(p[i].x(), p[i].y());
		
		if (tile) {
			QPointF tmp = coordToPos(tile->position());
			tmp -= prob;
			if (sqrt(tmp.x() * tmp.x() + tmp.y() * tmp.y()) < missmatch) {
				missmatch = sqrt(tmp.x() * tmp.x() + tmp.y() * tmp.y());
				whichONe = i;
			}
		} else {
			++missmatches;
		}
	}
	if (missmatches != p.size())
		return GameManager::get()->board()->getTileAxial(p[whichONe].x(), p[whichONe].y())->position();
	return GameManager::get()->board()->getTileAxial(0,0)->position();
}

void GameBoard::clearActions()
{
	mapActions_.clear();
	objectActions_.clear();
	QStringList actionList;
	infobox_->setActions(actionList);
	update();
}

void GameBoard::clearSelect()
{
	selectedObject_ = nullptr;
	clearActions();
	infobox_->setVisible(false);
}

void GameBoard::getActions()
{
	
	GMlog() << "Selected Object :" << selectedObject_->name() << "\n";
	clearActions();
	mapActions_ = GameManager::get()->mapActions(selectedObject_);
	objectActions_ = GameManager::get()->objectActions(selectedObject_);
	GMlog() << "possible object actions: ";
	QStringList actions;
	for (Action *a: objectActions_) {
	GMlog() << (QString)(a->type());
		if(a->type() == ActionType::CreateUnit)
			actions.push_back((QString)(static_cast<CreateUnitAction *>(a)->pType()));
		else
			actions.push_back((QString)(a->type()));
	}
	infobox_->setActions(actions);
	//zupdateować infobox
	infobox_->setObject(selectedObject_);
	infobox_->setVisible(true);
}

void GameBoard::select(const Tile *tile)
{
	if (selectedObject_ == nullptr) {
		QList<const Object *> objects = tile->getObjects();
		if ((objects.size() == 0) || (tile->visionState(GameManager::get()->currentPlayer()) == VisionType::Invisible)) {
			emit noSelection();
		} else {
			selectedObject_ = objects.first();
			selectedObjectID_ = selectedObject_->id();
			getActions();
		}
	} else if (selectedObject_->tile() == tile) {
		QList<const Object *> objects = tile->getObjects();
		selectedObject_ =  selectedObject_ == objects.first() ? objects.last() : objects.first();
		getActions();
	} else {
		for (Action *action : mapActions_)
			if (action->tile() == tile) {
				GMlog() << "Performing Action" << (QString)(action->type()) << "\n";
				GMlog() << "\tWith result :" << action->perform() << "\n";
				if (GameManager::get()->exists(selectedObjectID_)) {
					getActions();
					return;
				}
			}
		clearSelect();
		select(tile);
	}
}

void GameBoard::click(int mouseX, int mouseY, int x, int y, float scale)
{
	static const int BOARD_WIDTH = (BoardField::SIZE * GameManager::get()->board()->width() * 3 / 2 - BoardField::SIZE / 2);
	static const int BOARD_HEIGHT = BoardField::SIZE * sqrt(3) * GameManager::get()->board()->height();
	int x2 = (mouseX - x - (1 - scale) * BOARD_WIDTH / 2) / scale;
	int y2 = (mouseY - y - ( 1 - scale) * BOARD_HEIGHT / 2) / scale;
	QPoint clicked = pixelToHex(x2,y2);
	select(GameManager::get()->board()->getTile(clicked.x(), clicked.y()));
}

void GameBoard::makeAction(int action)
{
	if(action < objectActions_.length()) {
		objectActions_[action]->perform();
		select(selectedObject_->tile());
	}
}
 
BonusManager* GameBoard::bonusManager()
{
	return bonusManager_;
}

qint16 GameBoard::boardHeight()
{
	
	if (boardSet_) {
		return (BoardField::SIZE * sqrt(3) * GameManager::get()->board()->height());
	}
	return 0;
	
}

qint16 GameBoard::boardWidth()
{
	if (boardSet_) {
		return (BoardField::SIZE * GameManager::get()->board()->width() * 3 / 2 - BoardField::SIZE / 2);
	}
	return 0;
}

unsigned int GameBoard::getFood()
{
	return GameManager::get()->currentPlayer()->resource(Resource::Food);
}

unsigned int GameBoard::getGold()
{
	return GameManager::get()->currentPlayer()->resource(Resource::Gold);
}

unsigned int GameBoard::getResearch()
{
	return GameManager::get()->currentPlayer()->resource(Resource::Research);
}

void GameBoard::updateResources()
{
	emit resourcesUpdated();
}

void GameBoard::exit()
{
	selectedObject_ = nullptr;
	//qDeleteAll(mapActions_);
	//qDeleteAll(objectActions_);
	qDeleteAll(nodeMap);
	mapActions_.clear();
	objectActions_.clear();
	nodeMap.clear();
	boardSet_ = false;
}

QPointF GameBoard::boardCenter()
{
	return coordToPos(GameManager::get()->currentPlayer()->centralPositon()->position());
}
