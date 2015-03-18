#ifndef SNCONFIG_HPP
#define SNCONFIG_HPP

#include "SNTypes.hpp"

namespace SNCfg {
	/*
	 * Base cost of building
	 */
	const SNTypes::amount BUILDING_FOOD_COST = 50;
	const SNTypes::amount BUILDING_GOLD_COST = 50;
	const SNTypes::amount BUILDING_RESEARCH_COST = 50;
	
	/*
	 * Win conditions related constants
	 */
	const float DOMINATION_POPULATION_WIN_CONDITION = 0.6f;
	const float DOMINATION_LAND_WIN_CONDITION = 0.65f; 
	const float ECONOMIC_GOLD_WIN_CONDITION = 0.80f;
	const float ECONOMIC_GOLD_INCOME_WIN_CONDITION = 0.66f;
}

#endif