#pragma once
#include "pch.h"
#include "Walker.h"

#ifndef ZOMBIE_H_
#define ZOMBIE_H_

class Zombie : public Walker {
public: 
	Zombie() : Walker(1) {}
};

#endif 