#pragma once
#include <string>

#ifndef DENIZEN_H_
#define DENIZEN_H_

class Denizen {
private: 
	int age;
public: 
	Denizen(int age) : age(age) {}

	int get_age() const { return age; }
};

#endif