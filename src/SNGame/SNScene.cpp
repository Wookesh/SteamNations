#include "SNScene.hpp"
#include "SNHelpers.hpp"
#include "Graphics/TileGraphics.hpp"
#include "Graphics/TownGraphics.hpp"
#include "Graphics/UnitGraphics.hpp"
#include "../SNCore/Objects/Settler.hpp"
#include "../SNCore/Objects/Soldier.hpp"
#include "../SNCore/Objects/Town.hpp"
#include <QDebug>

SNScene::SNScene(GameManager *gameManager, QObject *parent) : QGraphicsScene(parent),
	selectedObject_(nullptr), gameManager_(gameManager)
{
	connect(gameManager_, &GameManager::objectCreated, this, &SNScene::createObject);
	createBoard();
}

SNScene::~SNScene()
{
	
}

void SNScene::createBoard()
{
	Board *b = gameManager_->board();
	for (Board::const_iterator tile = b->begin(); tile != b->end(); tile++) {
		createTile(*tile);
		for (const Object *object : (*tile)->getObjects())
			createObject(object->id());
	}
}


void SNScene::createObject(UID id)
{
	const Object *object = GameManager::get()->object(id);
	if (object == nullptr)
		return;
	
	if (object->type() ==  ObjectType::Town) {
		createTown(dynamic_cast<const Town *>(object));
	} else if (object->type() == ObjectType::Unit) {
		const Unit *unit = dynamic_cast<const Unit *>(object);
		
		if (unit->pType() == PrototypeType::Settler)
			createSettler(dynamic_cast<const Settler *>(unit));
		else
			createSoldier(dynamic_cast<const Soldier *>(unit));
	}
}

void SNScene::createTown(const Town *town)
{
	addItem(new TownGraphics(town));
}

void SNScene::connectUnit(const Unit *unit, UnitGraphics *unitG)
{
	connect(unit, &Unit::positionChanged, [unitG](){unitG->updatePosition();});
	connect(unit, &Object::objectDestroyed, [this, unitG](){removeItem(unitG); delete unitG;});
}

void SNScene::createSettler(const Settler *settler)
{
	UnitGraphics *unitG = new UnitGraphics(settler);
	addItem(unitG);
	connectUnit(settler, unitG);
}

void SNScene::createSoldier(const Soldier *soldier)
{
	UnitGraphics *unitG = new UnitGraphics(soldier);
	addItem(unitG);
	connectUnit(soldier, unitG);
}

void SNScene::createTile(const Tile *tile)
{
	TileGraphics *tileG = new TileGraphics(tile);
	tileToItem_[tile] = tileG;
	addItem(tileG);
}


const Object *SNScene::selectedObject() const
{
	return selectedObject_;
}

const QVector<Action *> &SNScene::objectActions() const
{
	return objectActions_;
}

void SNScene::getActions()
{
	
	qDebug() << "Selected Object :" << selectedObject_->name();
	clearActions();
	mapActions_ = gameManager_->mapActions(selectedObject_);
	objectActions_ = gameManager_->objectActions(selectedObject());
	highlightActions();
	emit selectionUpdate();
}

void SNScene::clearActions()
{
	clearHighlight();
	mapActions_.clear();
	update();
}

void SNScene::clearSelect()
{
	selectedObject_ = nullptr;
	clearActions();
	emit noSelection();
}


void SNScene::select(const Tile *tile)
{
	if (selectedObject_ == nullptr) {
		QList<const Object *> objects = tile->getObjects();
		if (objects.size() == 0) {
			emit noSelection();
		} else {
			selectedObject_ = objects.first();
			getActions();
		}
	} else if (selectedObject_->tile() == tile) {
		QList<const Object *> objects = tile->getObjects();
		selectedObject_ =  selectedObject_ == objects.first() ? objects.last() : objects.first();
		getActions();
	} else {
		for (Action *action : mapActions_)
			if (action->tile() == tile) {
				qDebug() << "Performing Action" << (QString)(action->type());
				qDebug() << "\tWith result :" << action->perform();
				getActions();
				return;
			}
		clearSelect();
		select(tile);
	}
}

void SNScene::setBoard(Board *board)
{
	
}

void SNScene::highlightActions()
{
	for (Action *action : mapActions_) {
		tileToItem_[action->tile()]->highlight(action->type());
	}
}

void SNScene::clearHighlight()
{
	for (Action *action : mapActions_) {
		tileToItem_[action->tile()]->highlight(ActionType::None);
	}
}


