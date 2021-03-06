#ifndef SPAWN_UNIT_ACTION_HPP
#define SPAWN_UNIT_ACTION_HPP

#include "Action.hpp"
#include "SNCore/Objects/Prototypes/Prototype.hpp"

class GameManager;
class Console;
class Player;

class SpawnUnitAction : public Action {
public:
	
	virtual bool perform() override;
protected:
	SpawnUnitAction(Player *player, Tile *tile, const PrototypeType &type);
	Player *player_;
	PrototypeType type_;
	
friend class GameManager;
friend class Console;
};

#endif