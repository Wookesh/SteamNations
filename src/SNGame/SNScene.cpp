#include "SNScene.hpp"
#include "SNHelpers.hpp"
#include "TownGraphics.hpp"

SNScene::SNScene(GameManager *gameManager, QObject *parent) : QGraphicsScene(parent),
	gameManager_(gameManager)
{
	Board *b = gameManager_->board();
	for (Board::const_iterator tile = b->begin(); tile != b->end(); tile++) {
			addItem(new TileGraphics(*tile));
			if ((*tile)->town() != nullptr)
				addItem(new TownGraphics((*tile)->town()));
	}
}

SNScene::~SNScene()
{

}

void SNScene::select(const Tile *tile)
{
	if (selectedObject_ == nullptr) {
		QList<const Object *> objects = tile->getObjects();
		if (objects.size() == 1) {
			selectedObject_ = objects.first();
			//highlightActions(game_->actions(selectedObject_));
		}
	} else {
		//for (SN::Action *action : possibleActions_)
			//if (action.finalTile == tile)
				//action.perform;
	}
}

void SNScene::setBoard(Board *board)
{

}

void SNScene::highlightActions()
{
	
}

