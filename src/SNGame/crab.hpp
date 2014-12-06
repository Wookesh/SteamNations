#ifndef CRAB_HPP
#define CRAB_HPP

#include <QtQuick/QQuickItem>
#include <QColor>
#include <QImage>


class Crab : public QQuickItem
{
	Q_OBJECT
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
protected:
	QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);

private:
	int frame_;

	static QTimer *timer_;

	static const QPixmap &images(int i);
	void initTimer();
private slots:
	void nextFrame();
};

#endif // CRAB_HPP



