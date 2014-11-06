#ifndef NEXTTURNBUTTON_HPP
#define NEXTTURNBUTTON_HPP
#include <QPushButton>

class NextTurnButton : public QPushButton {
Q_OBJECT
public:
	NextTurnButton(QWidget *parent = 0);
	virtual ~NextTurnButton();
	
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
public slots:
	void stopSpin();
};


#endif