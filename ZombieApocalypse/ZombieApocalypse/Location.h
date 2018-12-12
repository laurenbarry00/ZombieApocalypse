#pragma once
#include "pch.h"

#ifndef LOCATION_H_
#define LOCATION_H_

// Types defined by integer for easy of use in changing loc
// Numbered by desired layout within the BST 
enum class Location {
	DOWNTOWN = 3,
	UPTOWN = 1, 
	SOHO = 6, 
	THE_DOCKS = 2, 
	MEDICAL_HILL = 4, 
	U_DISTRICT = 5
};

#endif
