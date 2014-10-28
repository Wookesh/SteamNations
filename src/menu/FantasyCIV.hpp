#ifndef FANTASYCIV_HPP
#define FANTASYCIV_HPP

#include <QMainWindow>
#include <QStackedWidget>

class FantasyCIV : public QMainWindow {
Q_OBJECT
public:
	FantasyCIV(QWidget *parent = nullptr);
	virtual ~FantasyCIV();
private:
	int buildVersion_;
	QStackedWidget *widgets_;
	
	
	void createMenus();
};
#endif
