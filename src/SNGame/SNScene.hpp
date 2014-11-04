#ifndef SNSCENE_HPP
#define SNSCENE_HPP

#include <QGraphicsScene>
#include "../SNCore/Board.hpp"

class SNScene : public QGraphicsScene {
Q_OBJECT
public:
    SNScene(QObject *object);
    ~SNScene();
	void setBoard(Board *board);
	
protected:
	
private:
	
	
};



#endif