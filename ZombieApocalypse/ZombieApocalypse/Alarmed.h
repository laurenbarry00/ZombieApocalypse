#pragma once
#include "pch.h"
#include "Denizen.h"
#include "Walker.h"

#ifndef ALARMED_H_
#define ALARMED_H_

class Alarmed : public Denizen, public Walker {
public: 
	Alarmed(std::string name, int age) : 
		Denizen(name, age), Walker(2) {}
	
	int get_speed() const {
		return move_speed; 
	}
};

#endif 