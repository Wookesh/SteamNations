#ifndef CRAB_HPP
#define CRAB_HPP

#include <QtQuick/QQuickPaintedItem>
#include <QColor>


class Crab : public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(QColor color READ color WRITE setColor)
	Q_PROPERTY(int degree READ degree WRITE setDegree)
	Q_PROPERTY(int frame READ frame WRITE setFrame)

public:
	Crab(QQuickItem *parent = 0);

	QString name() const;
	void setName(const QString &name);

	QColor color() const;
	void setColor(const QColor &color);

	int degree() const;
	void setDegree(const int degree);

	int frame() const;
	void setFrame(const int frame);

	void paint(QPainter *painter);

private:
	QString m_name;
	QColor m_color;
	int degree_;
	int frame_;

};

#endif // CRAB_HPP



