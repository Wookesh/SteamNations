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
	
// 	enum class Type : quint8 {
// 		None,
// 		Move,
// 		Attack,
// 		Capture,
// 		Settle,
// 		CreateUnit
// 	};
// 	
// 	static QString name(Type type);
// 	static const QVector<Action::Type> &types();
	
	
	Action(Object *mainObject, Tile *tile, Type type);
	~Action();
	
	virtual bool perform() = 0;
	const Tile *tile() const;
	Type type() const;
protected:
	Type type_;
	Object *mainObject_;
	Tile *tile_;
};


#endif