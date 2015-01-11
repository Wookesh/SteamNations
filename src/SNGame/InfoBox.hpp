#ifndef INFOBOXHPP
#define INFOBOXHPP

#include <QObject>
#include <QString>

class InfoBox : public QObject {
Q_OBJECT

	
public:
	Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString owner READ owner WRITE setOwner NOTIFY ownerChanged)
	InfoBox(QObject *parent = 0);
	
	void setVisible(bool visible);
	bool visible();
	
	void setOwner(QString owner);
	QString owner();
	
	void setName(QString name);
	QString name();
signals:
	void visibleChanged();
	void nameChanged();
	void ownerChanged();
private:
	bool visible_;
	QString name_;
	QString owner_;

};





















#endif