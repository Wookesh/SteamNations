#ifndef ACTION_HPP
#define ACTION_HPP

#include <QtGlobal>
#include <QMap>

#include "../EnumHelpers.hpp"

class Object;
class Tile;

EnumClassWithStrings(ActionType, quint8, Attack, Capture, CreateUnit, Move, None, Settle)

class Action {
public:
	
// 	enum class ActionType : quint8 {
// 		None,
// 		Move,
// 		Attack,
// 		Capture,
// 		Settle,
// 		CreateUnit
// 	};
// 	
// 	static QString name(ActionType type);
// 	static const QVector<Action::ActionType> &types();
	
	
	Action(Object *mainObject, Tile *tile, ActionType type);
	~Action();
	
	virtual bool perform() = 0;
	const Tile *tile() const;
	ActionType type() const;
protected:
	ActionType type_;
	Object *mainObject_;
	Tile *tile_;
};


#endif