#include "Action.hpp"
#include <QMap>
#include <QVector>
#include <QString>

QString Action::name(Action::Type type)
{
	static const QMap<Type, QString> map({
		{Type::Attack, "Attack"},
		{Type::Capture, "Capture"},
		{Type::CreateUnit, "Create unit"},
		{Type::Move, "Move"},
		{Type::None, "None"},
		{Type::Settle, "Settle"},
	});
	return map[type];
}

const QVector<Action::Type> &Action::types()
{
	static const QVector<Action::Type> types_({
		Type::Attack, Type::Capture, Type::CreateUnit,
		Type::Move, Type::None, Type::Settle,
	});
	return types_;
}


Action::Action(Object *mainObject, Tile *tile, Type type) : type_(type), mainObject_(mainObject), tile_(tile)
{

}

Action::~Action()
{

}


const Tile *Action::tile() const
{
	return tile_;
}

Action::Type Action::type() const
{
	return type_;
}

