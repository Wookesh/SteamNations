#ifndef GRAPHICINTERFACE_H
#define GRAPHICINTERFACE_H

#include <QWidget>
#include "GameView.hpp"
#include <QResizeEvent>
#include <QPushButton>
#include "../SNCore/GameManager.hpp"

class GraphicInterface : public QWidget {
Q_OBJECT
public:
	GraphicInterface(QWidget *parent = nullptr);
	~GraphicInterface();
protected:
	void resizeEvent(QResizeEvent *event);
private:
	QPushButton *testButton_;
	GameView *gameView_;
	GameManager *gameManager_;
};

#endif
