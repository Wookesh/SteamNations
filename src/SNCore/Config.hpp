#ifndef SNCONFIG_HPP
#define SNCONFIG_HPP

#include <QString>

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
	const SNTypes::amount ECONOMIC_GOLD_MIN_GOLD = 1500;
	
	/*
	 * Techs cost
	 */
	const SNTypes::amount TECHNOLOGY_COST_TIER1 = 250;
	const SNTypes::amount TECHNOLOGY_COST_TIER2 = 500;
	const SNTypes::amount TECHNOLOGY_COST_TIER3 = 1000;
	
	/*
	 * Tech descriptions
	 */
	const QString WAR_TECH_DESCRIPTION_TIER1 = "Adds 10% more damage for all soldiers.";
	const QString WAR_TECH_DESCRIPTION_TIER2 = "Increase attack range by 1 for all soldiers.";
	const QString WAR_TECH_DESCRIPTION_TIER3 = "Increase movement range by 1 for all soldiers.";
	
	const QString DEF_TECH_DESCRIPTION_TIER1 = "Increase HP by 10% for all soldiers.";
	const QString DEF_TECH_DESCRIPTION_TIER2 = "Soldiers regenerate HP in friendly territory.";
	const QString DEF_TECH_DESCRIPTION_TIER3 = "Artillery gains ability to counterattack.";
	
	const QString ECO_TECH_DESCRIPTION_TIER1 = "Increase resource income by 10%.";
	const QString ECO_TECH_DESCRIPTION_TIER2 = "Increase Settler movement range by 1.";
	const QString ECO_TECH_DESCRIPTION_TIER3 = "Gold tiles generate double amount.";
}

#endif
