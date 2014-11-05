#include "SNScene.hpp"

SNScene::SNScene(QObject *object): QGraphicsScene(object)
{

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

