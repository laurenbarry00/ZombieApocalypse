#pragma once
#include "pch.h"
#include "Denizen.h" 
#include "Location.h" 

#ifndef IGNORANT_H_
#define IGNORANT_H_

class Ignorant : public Denizen {
private: 
	Location work; 
	Location home; 
public: 
	Ignorant(int age, Location work, Location home) :
		Denizen(age), work(work), home(home) {}

	Location get_home() const { return home; }

	Location get_workplace() const { return work; }
};

#endif 