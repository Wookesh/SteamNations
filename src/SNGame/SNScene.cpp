#include "SNScene.hpp"
#include "SNHelpers.hpp"
#include "TileGraphics.hpp"
#include "TownGraphics.hpp"
#include "UnitGraphics.hpp"
#include "../SNCore/Settler.hpp"
#include "../SNCore/Soldier.hpp"
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
	
	switch (object->type()) {
		case Object::Type::Town: {
			
			createTown(dynamic_cast<const Town *>(object));
			break;
		}
		case Object::Type::Unit: {
			const Unit *unit = dynamic_cast<const Unit *>(object);
			switch (unit->pType()) {
				case Prototype::Type::Settler : {
					createSettler(dynamic_cast<const Settler *>(unit));
					break;
				}
				case Prototype::Type::Soldier : {
					createSoldier(dynamic_cast<const Soldier *>(unit));
					break;
				}
			}
			break;
		}
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
		} else if (objects.size() == 1) {
			selectedObject_ = objects.first();
			getActions();
		}
	} else {
		for (Action *action : mapActions_)
			if (action->tile() == tile) {
				qDebug() << "Performing Action" << Action::name(action->type());
				qDebug() << "\tWith result :" << action->perform();
				clearActions();
				getActions();
				return;
			}
		clearSelect();
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
		tileToItem_[action->tile()]->highlight(Action::Type::None);
	}
}


