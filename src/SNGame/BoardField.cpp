#include "BoardField.hpp"
#include "SNCore/Objects/Town.hpp"
#include "SNCore/Objects/Unit.hpp"
#include "SNCore/Actions/Actions.hpp"
#include "SNCore/Resources.hpp"
#include "SNCore/Tile.hpp"


BoardField::BoardField(QSGNode* node,Tile *tile) :
	node_(node), unit_(tile->unit()), town_(tile->town()), tile_(tile), highlighted_(false)
{
	//qDebug() << "bf";
}

QSGNode *BoardField::node()
{
	return node_;
}

void BoardField::setTown( Town* town)
{
	town_ = town;
}

const Town *BoardField::town()
{
	return town_;
}

void BoardField::setUnit( Unit* unit)
{
	unit_ = unit;
}

const Unit *BoardField::unit()
{
	return unit_;
}

void BoardField::highlight()
{
	highlighted_ = true;
}

void BoardField::unhighlight()
{
	highlighted_ = false;
}

QColor BoardField::highlightColor(ActionType type)
{
	static const QHash<ActionType, QColor> map({
		{ActionType::Attack, Qt::red},
		{ActionType::Capture, Qt::magenta},
		{ActionType::Move, Qt::cyan},
		{ActionType::None, Qt::white},
		{ActionType::Settle, Qt::yellow},
		{ActionType::CreateUnit, Qt::darkYellow}
	});
	return map[type];
}

QColor BoardField::tileColor()
{
	static const QHash<Resource, QColor> map({
		{Resource::Food, Qt::darkGreen},
		{Resource::Research, Qt::darkBlue},
		{Resource::Gold, Qt::yellow},
		{Resource::None, Qt::darkRed}
	});
	return map[tile_->resource()];
}
