#ifndef OBJECTINFOBOX_HPP
#define OBJECTINFOBOX_HPP
#include <QWidget>
#include <QLabel>
#include "../SNCore/Town.hpp"
#include "../SNCore/Unit.hpp"
#include "../SNCore/Action.hpp"

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
private:
	QLabel *nameDisplay_;
};

#endif