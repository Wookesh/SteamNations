#ifndef INFOBOXHPP
#define INFOBOXHPP

#include <QObject>
#include <QString>
#include <QStringList>

class Object;

class InfoBox : public QObject {
Q_OBJECT

	
public:
	Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
	Q_PROPERTY(QString name READ name )
	Q_PROPERTY(QString owner READ owner)
	Q_PROPERTY(QStringList actions READ actions)
	Q_PROPERTY(Object *object NOTIFY objectChanged)
	InfoBox(QObject *parent = 0);
	
	void setVisible(bool visible);
	void setObject(const Object *object);
	void setActions(QStringList &actions);
	bool visible();
	QString owner();
	QString name();
	QStringList &actions();
signals:
	void objectChanged();
	void visibleChanged();
private:
	bool visible_;
	const Object *selectedObject_;
	QStringList objectActions_;

};





















#endif