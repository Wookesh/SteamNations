#include "Action.hpp"
#include <QMap>
#include <QString>

QString Action::name(Action::Type type)
{
	static QMap<Type, QString> map({
		{Type::Attack, "Attack"},
		{Type::Capture, "Capture"},
		{Type::Move, "Move"},
		{Type::None, "None"},
		{Type::Settle, "Settle"}
	});
	return map[type];
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

