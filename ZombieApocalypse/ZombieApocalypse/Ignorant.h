#pragma once
#include "Denizen.h" 
#include "Location.h" 

#ifndef IGNORANT_H_
#define IGNORANT_H_

class Ignorant : Denizen {
private: 
	Location work; 
	Location home; 
public: 
	Ignorant(std::string name, int age, Location work, Location home) :
		Denizen(name, age), work(work), home(home) {}

	Location get_home() const { return home; }

	Location get_workplace() const { return work; }
};

#endif 