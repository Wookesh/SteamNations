#ifndef INFOBOXHPP
#define INFOBOXHPP

#include <QObject>
#include <QString>
#include <QStringList>
#include "SNCore/SNTypes.hpp"

class Object;

class InfoBox : public QObject {
Q_OBJECT
public:
	Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
	Q_PROPERTY(QString name READ name )
	Q_PROPERTY(QString owner READ owner)
	Q_PROPERTY(QStringList actions READ actions)
	Q_PROPERTY(qint16 healthLeft READ healthLeft)
	Q_PROPERTY(qint16 health READ health)
	
	InfoBox(QObject *parent = 0);
	
	void setVisible(bool visible);
	void setObject(const Object *object);
	void setActions(QStringList &actions);
	bool visible();
	QString owner();
	QString name();
	qint16 health();
	qint16 healthLeft();
	QStringList &actions();
signals:
	void objectChanged();
	void townChanged();
	void unitChanged();
	void visibleChanged();
private:
	bool visible_;
	const Object *selectedObject_;
	QStringList objectActions_;

};





















#endif