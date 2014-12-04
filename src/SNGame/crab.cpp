#include "crab.hpp"
#include <QPainter>
#include <QDebug>

Crab::Crab(QQuickItem *parent)
	: QQuickPaintedItem(parent),frame_(0)
{
}

QString Crab::name() const
{
	return m_name;
}

void Crab::setName(const QString &name)
{
	m_name = name;
}

QColor Crab::color() const
{
	return m_color;
}

void Crab::setColor(const QColor &color)
{
	m_color = color;
}

void Crab::setDegree(const int degree)
{
	degree_ = degree;

}

int Crab::degree() const
{
	return degree_;
}

int Crab::frame() const
{
	return frame_;
}

void Crab::setFrame(const int frame)
{
	frame_ = frame % 8;
	update();
}


void Crab::paint(QPainter *painter)
{



	QPixmap texture = QPixmap(":/melee-idle.png");
	//texture.fill(Qt::red);
	painter->drawPixmap(0,0,64,64,texture, frame_*64,0,64,64);/*
	QPen pen(Qt::blue, 5);
	painter->setPen(pen);
	painter->drawRect(0,0,100,100);*/


}

