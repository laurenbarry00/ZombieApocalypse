#pragma once
#include "Denizen.h"
#include "Walker.h"

#ifndef ALARMED_H_
#define ALARMED_H_

class Alarmed : Denizen, Walker {
public: 
	Alarmed(std::string name, int age) : 
		Denizen(name, age), Walker(2) {}
};

#endif 