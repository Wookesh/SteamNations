#ifndef OBJECTINFOBOX_HPP
#define OBJECTINFOBOX_HPP
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "../SNCore/Town.hpp"
#include "../SNCore/Unit.hpp"
#include "../SNCore/Action.hpp"


class StatDisplay : public QLabel {
Q_OBJECT
public:
	explicit StatDisplay(const QString &stat, QWidget *parent = nullptr);
	
	void setValue(int v);
private:
	QString stat_;
	int val_;
};


class ActionButton : public QPushButton {
Q_OBJECT
public:
	ActionButton(Action::Type type, QWidget *parent = nullptr);
	void addAction(Action *action);
	void clear();
private:
	QVector<Action *> actions_;
	Action::Type type_;
private slots:
	void perform();
signals:
	void performed();
};


class ObjectInfoBox : public QWidget {
Q_OBJECT
public:
	ObjectInfoBox(QWidget *parent = nullptr);
	virtual ~ObjectInfoBox();
	
	void setObject(const Object *object, const QVector<Action *> &actions);
	
	virtual QSize minimumSizeHint() const;
	virtual QSize sizeHint() const;
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void resizeEvent(QResizeEvent *);
private:
	QLabel *nameDisplay_;
	StatDisplay *unitRange_;
	StatDisplay *unitDamage_;
	StatDisplay *unitMoveRange_;
	QMap<Action::Type, ActionButton *> actionButtons_;
	
	int displayed_;
	void displayStat(StatDisplay *stat);
	void displayButton(ActionButton *button);
private slots:
	void hideAll();
signals:
	void actionPerformed();
};


#endif