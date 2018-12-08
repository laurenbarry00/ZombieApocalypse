#pragma once
#include "Denizen.h" 
#include "Location.h" 

#ifndef IGNORANT_H_
#define IGNORANT_H_

// This class structure reflects the changes I've proposed in District design
class Ignorant : Denizen {
private: 
	Location work; 
	Location home; 
public: 
	Ignorant(std::string name, int age, Location work, Location home) :
		Denizen(name, age), work(work), home(home) {}
};

#endif 