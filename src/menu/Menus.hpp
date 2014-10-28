#ifndef MENUS_HPP
#define MENUS_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

/*
 * Menu (abstract)
 */
class Menu :public QWidget {
Q_OBJECT
public:
	Menu(QWidget *parent = nullptr);
	virtual ~Menu();
protected:
	virtual void createLayout() = 0;
	template <class T>
	void setButtons(QList<QPair<QString, void (T::*)()>> &list, T *object)
	{
		QVBoxLayout *layout = new QVBoxLayout();
		for (QPair<QString, void (T::*)()> p: list) {
			QPushButton *b = new QPushButton(p.first);
			connect(b, &QPushButton::clicked, object, p.second);
			layout->addWidget(b);
		}
		setLayout(layout);
	}
};



/*
 * MainMenu
 */

class MainMenu : public Menu {
Q_OBJECT
public:
	MainMenu(QWidget *parent = nullptr);
	virtual ~MainMenu();
protected:
	virtual void createLayout() override;
signals:
	void newGame();
	void loadGame();
	void options();
	void exit();
};


/*
 * PlayMenu
 */

class PlayMenu : public Menu {
Q_OBJECT
public :
	PlayMenu(QWidget *parent = nullptr);
	virtual ~PlayMenu();
protected:
	virtual void createLayout() override;
signals:
	void back();
};

/*
 * OptionsMenu
 */

class OptionsMenu : public Menu {
Q_OBJECT
public :
	OptionsMenu(QWidget *parent = nullptr);
	virtual ~OptionsMenu();
protected:
	virtual void createLayout() override;
signals:
	void back();
};

#endif