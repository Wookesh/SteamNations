#include <QPainter>
#include <QDebug>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <QTimer>
#include <QDebug>
#include "Board.hpp"

QTimer *Board::timer_ = nullptr;

void Board::initTimer()
{
	if (timer_ == nullptr) {
		timer_ = new QTimer();
		timer_->setInterval(250);
		timer_->start();
	}
	connect(timer_, &QTimer::timeout, this, &Board::nextFrame);
}

void Board::nextFrame()
{
	qDebug() << "update";

	update();

}

Board::Board(QQuickItem *parent)
	: QQuickItem(parent)
{
	setFlag(QQuickItem::ItemHasContents, true);
	initTimer();
}

int Board::index(int x, int y)
{
	return x + y * 30;
}

QSGNode *Board::updatePaintNode(QSGNode *mainNode, UpdatePaintNodeData *)
{
	QSGNode *node = mainNode;
	if (!node) {
		node = new QSGNode();
		for(int i = 0; i < 50; i++) {
			for(int j = 0; j < 50; j++) {
				QSGGeometryNode *child = new QSGGeometryNode();
				QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 6);
				geometry->setDrawingMode(GL_LINE_LOOP);
				geometry->setLineWidth(3);
				int addX, addY;
				addX = 48 * i;
				addY = i%2 ? 56 * j : 56 * j + 28;

				geometry->vertexDataAsPoint2D()[0].set(16 + addX, 0 + addY);
				geometry->vertexDataAsPoint2D()[1].set(48 + addX, 0 + addY);
				geometry->vertexDataAsPoint2D()[2].set(64 + addX, 28 + addY);
				geometry->vertexDataAsPoint2D()[3].set(48 + addX, 56 + addY);
				geometry->vertexDataAsPoint2D()[4].set(16 + addX, 56 + addY);
				geometry->vertexDataAsPoint2D()[5].set(0 + addX, 28 + addY);
				QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
				material->setColor(QColor(0, 255, 0));

				child->setGeometry(geometry);
				child->setFlag(QSGNode::OwnsGeometry);
				child->setMaterial(material);
				child->setFlag(QSGNode::OwnsMaterial);
				nodeMap[index(i, j)] = child;
				node->appendChildNode(child);
			}
		}
	}
	return node;
}
