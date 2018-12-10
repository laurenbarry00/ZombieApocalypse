#pragma once

#include "Location.h"
#include "Ignorant.h"
#include "Alarmed.h"
#include "Zombie.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

class Simulator {
private:
	const int NUM_DAYS;
	const int START_ZOMBS;
	const Location START_LOC;
	const double IGNORANT_BITTEN_RATIO;
	const double ALARMED_BITTEN_RATIO;

	int time_of_day; // 0 = morning, 1 = afternoon, 2 = evening
	int days_run;

	std::unordered_map<Ignorant, Location> ignorant;
	std::unordered_map<Alarmed, Location> alarmed;
	std::unordered_map<Zombie, Location> zombie;

	void tick() {
		switch (time_of_day) {
			case 0: // Morning
				// No movement in this phase.
				// Considering removing bite/alarm attempt here as well. Morning could be like, a "check-in" period
				// without any actions taking place.
				attempt_bite_and_alarm();
				std::cout << "DAY " << days_run << ", MORNING" << std::endl;
				print_simulation_report();
				time_of_day++;
				break;

			case 1: // Afternoon
				commute_work();
				attempt_bite_and_alarm();
				std::cout << "DAY " << days_run << ", AFTERNOON" << std::endl;
				print_simulation_report();
				time_of_day++;
				break;

			case 2: // Evening
				commute_home();
				attempt_bite_and_alarm();
				std::cout << "DAY " << days_run << ", EVENING" << std::endl;
				print_simulation_report();
				days_run++;
				time_of_day = 0;
				break;
		}
	}

	void print_simulation_report() {
		std::cout << "Ignorant: " << ignorant.size() << std::endl;
		std::cout << "Alarmed: " << alarmed.size() << std::endl;
		std::cout << "Zombies: " << zombie.size() << std::endl;
		std::cout << std::endl;
	}

	void attempt_bite_and_alarm() {
		std::unordered_map<Alarmed, Location>::iterator itr;
		for (itr = alarmed.begin(); itr != alarmed.end(); ++itr) {
			// TODO: Implement bite/alarm attempt
		}
	}

	std::vector<Denizen> get_denizens_by_location(std::unordered_map<Denizen, Location> map, Location loc) {
		std::vector<Denizen> denizens_in_location;
		std::unordered_map<Denizen, Location>::iterator itr;
		for (itr = map.begin(); itr != map.end(); ++itr) {
			/* TODO: Implement get_denizens_by_location()
			if (map.find(itr->first) == loc) {
				denizens_in_location.push_back(map.find(itr->first));
			}
			*/
		}
	}

	// IGNORANT 
	// there should be a better way to do this than having two sep. functions
	// that are essentially the same and will run one after the other, based on the time clicks.
	// Maybe we could have the function pause for a few seconds?
	// ignorant citizen's journey to work and back home. 
	// Right now, our implementation assumes that everyone gets to work by the afternoon. 

	// We should also think about calling our functions async to make the simulator more realistic

	// Changed these two functions to private, since the only function outside classes will need to access is run()
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

public:
	Simulator(int days, int zombies, Location loc, double ign_ratio, double alrm_ratio)
		: NUM_DAYS(days), START_ZOMBS(zombies), START_LOC(loc), IGNORANT_BITTEN_RATIO(ign_ratio), ALARMED_BITTEN_RATIO(alrm_ratio) {
		time_of_day = 0; // Begins in the morning
		days_run = 0;
	}


	/*
	 * Default constructor for Simulator class
	 * This has practically no time limit for the simulation to run, so it will run until all ignorant and alarmed are bitten successfully. 
	 * We might have to play around with the default ratios to see what's reasonable, as well as the number of zombies at the start.
	 */
	Simulator() : NUM_DAYS(999), START_ZOMBS(1), START_LOC(Location::U_DISTRICT), IGNORANT_BITTEN_RATIO(30), ALARMED_BITTEN_RATIO(20) {
		time_of_day = 0;
		days_run = 0;
	}

	void run() {
		do {
			if (days_run == NUM_DAYS) {
				std::cout << std::endl;
				std::cout << "SIMULATION ENDED: DAY " << days_run << std::endl;
				print_simulation_report();
				break;
			}
		} while (ignorant.size() > 0 || alarmed.size() > 0);
	}
};

#endif 