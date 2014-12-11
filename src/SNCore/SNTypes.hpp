#ifndef SNTYPES_HPP
#define SNTYPES_HPP

#include <QtCore/QtGlobal>

namespace SNTypes {
	
	/**
	 * HealthModifier
	 */
	typedef quint16 healthBasedType;
	
	/**
	 * HealthPoints
	 */
	typedef healthBasedType hp;
	
	/**
	 * Damage
	 */
	typedef healthBasedType dmg;
	
	/**
	 * ActionPoinst
	 */
	typedef quint16 ap;
	
	/**
	 * Distance
	 */
	typedef ap distance;
	
	/**
	 * Amount of Resource
	 */
	typedef quint16 amount;
}

#endif