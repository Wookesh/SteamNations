#ifndef INFOBOXHPP
#define INFOBOXHPP

#include <QObject>
#include <QString>

class Object;

class InfoBox : public QObject {
Q_OBJECT

	
public:
	Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
	Q_PROPERTY(QString name READ name )
	Q_PROPERTY(QString owner READ owner)
	Q_PROPERTY(Object *object NOTIFY objectChanged)
	InfoBox(QObject *parent = 0);
	
	void setVisible(bool visible);
	void setObject(const Object *object);
	bool visible();
	QString owner();
	QString name();
signals:
	void objectChanged();
	void visibleChanged();
private:
	bool visible_;
	const Object *selectedObject_;

};





















#endif