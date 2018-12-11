#pragma once
#include "pch.h"

#include "Location.h"
#include "Ignorant.h"
#include "Alarmed.h"
#include "Zombie.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>

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

	std::vector<Location> locations = { Location::DOWNTOWN, Location::MEDICAL_HILL, Location::SOHO, Location::THE_DOCKS, Location::UPTOWN, Location::U_DISTRICT };

	std::unordered_map<Ignorant, Location> ignorant;
	std::unordered_map<Alarmed, Location> alarmed;
	std::unordered_map<Zombie, Location> zombie;

	void tick() {
		switch (time_of_day) {
			case 0: // Morning
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
		for (int i = 0; i < locations.size(); i++) {
			std::vector<Alarmed> alarmed_in_loc = get_keys_by_location(alarmed, locations.at(i));
			std::vector<Ignorant> ignorant_in_loc = get_keys_by_location(ignorant, locations.at(i));
			for (Ignorant ig : ignorant_in_loc) {
				Alarmed a = Alarmed(ig.get_name, ig.get_age);
				alarmed.insert(std::make_pair(a, locations.at(i)));
				ignorant.erase(ig); // Remove ignorant and "move" it to alarmed
			}

			std::vector<Zombie> zombies_in_loc = get_keys_by_location(zombie, locations.at(i));
			for (int i = 0; i < zombies_in_loc.size(); i++) {
				int alarmed_or_ignorant = rand() % 2; // Choosing between whether the zombie bites an alarmed or an ignorant
				if (alarmed_or_ignorant == 1) {
					int ignorant_index = rand() % (ignorant_in_loc.size() + 1); // a random index
					double probability = (double) rand() / 100;
					if (probability < IGNORANT_BITTEN_RATIO) {
						Zombie z = Zombie();
						zombie.insert(std::make_pair(z, locations.at(i)));
						ignorant.erase(ignorant_in_loc.at(ignorant_index));
					}
				}
				else {
					int alarmed_index = rand() % (alarmed_in_loc.size() + 1); // a random index
					double probability = (double)rand() / 100;
					if (probability < IGNORANT_BITTEN_RATIO) {
						Zombie z = Zombie();
						zombie.insert(std::make_pair(z, locations.at(i)));
						alarmed.erase(alarmed_in_loc.at(alarmed_index));
					}
				}
			}
		}
	}

	template <typename T> std::vector<T> get_keys_by_location(std::unordered_map<T, Location> map, Location loc) {
		std::unordered_map<T, Location>::iterator itr;
		std::vector<T> keys;
		for (itr = map.begin(); itr != map.end(); ++itr) {
			if (itr->second == loc) {
				keys.push_back(itr->first);
			}
		}
		return keys;
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

	void shuffle() {
		// alarmed 
		std::unordered_map<Alarmed, Location>::iterator itr;
		for (itr = alarmed.begin(); itr != alarmed.end(); ++itr) {
			Location current = itr->second;
			// implement probability
		}

		// zombs 
		// iterate over list of alarmed or zombs 
		// get current location 
		// place current location based on binary tree 
		// based on speed, choose random direction to go 
	}

public:
	Simulator(int days, int zombies, int denizens, Location loc, double ign_ratio, double alrm_ratio)
		: NUM_DAYS(days), START_ZOMBS(zombies), START_LOC(loc), IGNORANT_BITTEN_RATIO(ign_ratio), ALARMED_BITTEN_RATIO(alrm_ratio), time_of_day(0), days_run(0) {
		int denizens_populated = 0;

		// create the zombie(s) and place them in the start location
		for (int i = 0; i < zombies; i++) {
			Zombie z = Zombie();
			zombie.insert(std::make_pair(z, loc));
			denizens_populated++;
		}

		std::ifstream names_file;
		names_file.open("residents.txt");
		
	}


	/*
	 * Default constructor for Simulator class
	 * This has practically no time limit for the simulation to run, so it will run until all ignorant and alarmed are bitten successfully. 
	 * We might have to play around with the default ratios to see what's reasonable, as well as the number of zombies at the start.
	 */
	Simulator() : NUM_DAYS(999), START_ZOMBS(1), START_LOC(Location::U_DISTRICT), IGNORANT_BITTEN_RATIO(0.30), ALARMED_BITTEN_RATIO(0.20) {
		time_of_day = 0;
		days_run = 0;
		int denizens_populated = 0;

		Zombie z = Zombie();
		zombie.insert(std::make_pair(z, Location::U_DISTRICT));
		denizens_populated++;
		do {
			
		} while (denizens_populated < 30); // Defaults to 30 denizens in the simulation
	}

	void create_tree() {

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