#include "Action.hpp"
#include <QMap>
#include <QVector>
#include <QString>

// QString Action::name(Action::ActionType type)
// {
// 	static const QMap<ActionType, QString> map({
// 		{ActionType::Attack, "Attack"},
// 		{ActionType::Capture, "Capture"},
// 		{ActionType::CreateUnit, "Create unit"},
// 		{ActionType::Move, "Move"},
// 		{ActionType::None, "None"},
// 		{ActionType::Settle, "Settle"},
// 	});
// 	return map[type];
// }
// 
// const QVector<Action::ActionType> &Action::types()
// {
// 	static const QVector<Action::ActionType> types_({
// 		ActionType::Attack, ActionType::Capture, ActionType::CreateUnit,
// 		ActionType::Move, ActionType::None, ActionType::Settle,
// 	});
// 	return types_;
// }


Action::Action(Object *mainObject, Tile *tile, ActionType type) : type_(type), mainObject_(mainObject), tile_(tile)
{

}

Action::~Action()
{

}


const Tile *Action::tile() const
{
	return tile_;
}

ActionType Action::type() const
{
	return type_;
}

