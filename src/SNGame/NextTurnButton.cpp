#include "NextTurnButton.hpp"

NextTurnButton::NextTurnButton(QWidget *parent): QPushButton(tr("Next Turn"), parent)
{

}

QSize NextTurnButton::minimumSizeHint() const
{
	return QPushButton::sizeHint();
}

QSize NextTurnButton::sizeHint() const
{
	return QSize(180, 180);
}


NextTurnButton::~NextTurnButton()
{

}

void NextTurnButton::stopSpin()
{

}
