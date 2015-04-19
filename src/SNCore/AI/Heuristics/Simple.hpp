#ifndef SIMPLE_HPP
#define SIMPLE_HPP

#include <limits>
#include <algorithm>
#include "SNCore/SNTypes.hpp"
#include "SNCore/Tile.hpp"
#include "SNCore/Objects/Objects.hpp"
#include "SNCore/Player.hpp"

namespace SimpleHeuristic {
	SNTypes::heur economyHeuristic(Player* player); //budowac jednostki czy budynki
	SNTypes::heur townBuildBuildingHeuristic(Town* town); //czy dobry town do budowania budynkow
	SNTypes::heur townBuildUnitHeuristic(Town* town); // czy dobry town do budowania jednostek
	SNTypes::heur soldierHeuristic(Soldier* soldier, Tile* tile); //ocena tile'a przez soldiera
	SNTypes::heur settlerHeuristic(Settler* settler, Tile* tile); //ocena tile'a przez settlera 
	SNTypes::heur settlerSettleHeuristic(Settler *settler, Tile *tile); //ocena tile do settlowania przez settlera
}


#endif