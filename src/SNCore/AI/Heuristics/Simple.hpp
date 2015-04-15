#ifndef SIMPLE_HPP
#define SIMPLE_HPP

#include "SNCore/SNTypes.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/Objects/Objects.hpp"

class Simple {
public:
	static SNTypes::heur unitHeuristic(Unit *unit, Tile *tile);
	static SNTypes::heur economyHeuristic(Player *player);
	static SNTypes::heur townBuildBuildingHeuristic(Town *town);
	static SNTypes::heur townBuildUnitHeuristic(Town *town);
protected:
	static SNTypes::heur soldierTownValue(Soldier *soldier, Town *town);
	static SNTypes::heur soldierUnitValue(Soldier *soldier, Unit *unit);
	static SNTypes::heur settlerTownValue(Settler *settler, Town *town);
	static SNTypes::heur unitWanderValue(Unit *unit, Tile *tile);
};


#endif