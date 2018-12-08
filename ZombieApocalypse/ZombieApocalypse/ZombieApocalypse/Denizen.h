#pragma once
#include <string>

#ifndef DENIZEN_H_
#define DENIZEN_H_

class Denizen {
private: 
	std::string name; 
	int age;
public: 
	Denizen(std::string name, int age) : name(name), age(age) {}
	virtual std::string get_name(); 
	virtual int get_age(); 
};

#endif