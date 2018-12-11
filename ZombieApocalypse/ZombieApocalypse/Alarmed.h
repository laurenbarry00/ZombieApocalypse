#pragma once
#include "pch.h"
#include "Denizen.h"
#include "Walker.h"

#ifndef ALARMED_H_
#define ALARMED_H_

class Alarmed : public Denizen, public Walker {
private: 
	const int move_speed;
public: 
	Alarmed(int age, int move_speed) : 
		Denizen(age), move_speed(move_speed), Walker(2) {}

	const int get_speed() {
		return move_speed;
	}
};

#endif 