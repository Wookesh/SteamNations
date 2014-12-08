#include "crab.hpp"
#include <QPainter>
#include <QDebug>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <QTimer>
#include <QDebug>

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

	QSGGeometryNode *node = static_cast<QSGGeometryNode *>(mainNode);
	if (!node) {
		node = new QSGGeometryNode();

	}
	QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 12);
	geometry->setDrawingMode(GL_LINES);
	geometry->setLineWidth(3);
	geometry->vertexDataAsPoint2D()[0].set(16, 0);
	geometry->vertexDataAsPoint2D()[1].set(48, 0);
	geometry->vertexDataAsPoint2D()[2].set(48, 0);
	geometry->vertexDataAsPoint2D()[3].set(64, 28);
	geometry->vertexDataAsPoint2D()[4].set(64, 28);
	geometry->vertexDataAsPoint2D()[5].set(48, 56);
	geometry->vertexDataAsPoint2D()[6].set(48, 56);
	geometry->vertexDataAsPoint2D()[7].set(16, 56);
	geometry->vertexDataAsPoint2D()[8].set(16, 56);
	geometry->vertexDataAsPoint2D()[9].set(0, 28);
	geometry->vertexDataAsPoint2D()[10].set(0, 28);
	geometry->vertexDataAsPoint2D()[11].set(16, 0);
	QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
	material->setColor(QColor(0, 255, 0));

	node->setGeometry(geometry);
	node->setFlag(QSGNode::OwnsGeometry);
	node->setMaterial(material);
	node->setFlag(QSGNode::OwnsMaterial);

	return node;
}

