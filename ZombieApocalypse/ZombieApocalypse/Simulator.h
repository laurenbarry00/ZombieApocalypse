#pragma once

#include "Location.h"
#include "Ignorant.h"
#include "Alarmed.h"
#include "Zombie.h"
#include <unordered_map>

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

class Simulator {
private:
	const int NUM_DAYS;
	const int START_ZOMBS;
	const Location START_LOC;
	const double IGNORANT_BITTEN_RATIO;
	const double ALARMED_BITTEN_RATIO;

	std::unordered_map<Ignorant, Location> ignorant;
	std::unordered_map<Alarmed, Location> alarmed;
	std::unordered_map<Zombie, Location> zombie;
public:
	Simulator(int days, int zombies, Location loc, double ign_ratio, double alrm_ratio)
		: NUM_DAYS(days), START_ZOMBS(zombies), START_LOC(loc), IGNORANT_BITTEN_RATIO(ign_ratio), ALARMED_BITTEN_RATIO(alrm_ratio) {}

	// IGNORANT 
	// there should be a better way to do this than having two sep. functions
	// that are essentially the same and will run one after the other, based on the time clicks.
	// Maybe we could have the function pause for a few seconds?
	// ignorant citizen's journey to work and back home. 
	// Right now, our implementation assumes that everyone gets to work by the afternoon. 

	// We should also think about calling our functions async to make the simulator more realistic
	void commute_work() {
		std::unordered_map<Ignorant, Location>::iterator itr; 
		for (itr = ignorant.begin(); itr != ignorant.end(); ++itr) {
			itr->second = itr->first.get_workplace; 
		}
	}

	void commute_home() {
		std::unordered_map<Ignorant, Location>::iterator itr;
		for (itr = ignorant.begin(); itr != ignorant.end(); ++itr) {
			itr->second = itr->first.get_home(); 
		}
	}
};

#endif 