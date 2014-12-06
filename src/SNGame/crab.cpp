#include "crab.hpp"
#include <QPainter>
#include <QDebug>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGNode>
#include <QTimer>

QTimer *Crab::timer_ = nullptr;

void Crab::initTimer()
{
	if (timer_ == nullptr) {
		timer_ = new QTimer();
		timer_->setInterval(25);
		timer_->start();
	}
	connect(timer_, &QTimer::timeout, this, &Crab::nextFrame);
}

void Crab::nextFrame()
{
	frame_ = (frame_ + 1) % 8;
	update();
}


const QPixmap &Crab::images(int i)
{
	static const QVector<QPixmap> images_ = []{
		QVector<QPixmap> result;
		QPixmap base(":/melee-idle.png");
		qDebug() << base.size() << base.isNull();
		for (int i = 0; i < 8; ++i) {
			result.push_back(base.copy(i * 64, 0, 64, 64));
			qDebug() << result[i].size();
		}
		qDebug() << "initialized";
		return result;
		}();
	return images_[i];
}


Crab::Crab(QQuickItem *parent)
	: QQuickItem(parent), frame_(0)
{
	setFlag(QQuickItem::ItemHasContents, true);
	initTimer();
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

QSGNode *Crab::updatePaintNode(QSGNode *mainNode, UpdatePaintNodeData *)
{
	QSGSimpleTextureNode *n = static_cast<QSGSimpleTextureNode *>(mainNode);
	if (!n) {
		n = new QSGSimpleTextureNode();
		n->setRect(x(), y(), 64, 64);
	}
	static QSGTexture *texture_ = nullptr;
	if (texture_ != nullptr)
		delete texture_;
	texture_ = window()->createTextureFromImage(images(frame_).toImage());
	n->setTexture(texture_);
	return n;
}

