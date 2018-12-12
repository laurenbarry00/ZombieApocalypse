#pragma once
#include "pch.h"

#include "Location.h"
#include "Ignorant.h"
#include "Alarmed.h"
#include "Zombie.h"
#include "District.h"
#include <Windows.h>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

class Simulator {
private:
	District<int>* root = new District<int>(3); 

	int NUM_DAYS; // the number of days the simulation should run 
	int START_ZOMBS; // the number of initial zombies
	Location START_LOC; // where the zombie infection starts from 
	double IGNORANT_BITTEN_RATIO; // probability that an ignorant person will become bitten 
	double ALARMED_BITTEN_RATIO; // probability that an alarmed person will be bitten

	int time_of_day; // 0 = morning, 1 = afternoon, 2 = evening
	int days_run;
	
	// temporary - for ease of use in short-term solution 
	std::vector<Location> locations = { Location::DOWNTOWN, Location::MEDICAL_HILL, Location::SOHO, Location::THE_DOCKS, Location::UPTOWN, Location::U_DISTRICT };

	std::unordered_map<Ignorant, Location> ignorant;
	std::unordered_map<Alarmed, Location> alarmed;
	std::unordered_map<Zombie, Location> zombie;

	// Controls the time clicks, going between morning, afternoon, and evening
	void tick() {
		switch (time_of_day) {
			case 0: // Morning
				// No movement in this phase
				attempt_bite_and_alarm();
				std::cout << "DAY " << days_run << ", MORNING" << std::endl;
				print_simulation_report();
				time_of_day++;
				break;

			case 1: // Afternoon
				commute_work();
				shuffle();
				attempt_bite_and_alarm();
				std::cout << "DAY " << days_run << ", AFTERNOON" << std::endl;
				print_simulation_report();
				time_of_day++;
				break;

			case 2: // Evening
				commute_home();
				shuffle();
				attempt_bite_and_alarm();
				std::cout << "DAY " << days_run << ", EVENING" << std::endl;
				print_simulation_report();
				days_run++;
				time_of_day = 0;
				break;
		}
	}

	// Prints update of SimVille situation
	void print_simulation_report() {
		std::cout << "Ignorant: " << ignorant.size() << std::endl;
		std::cout << "Alarmed: " << alarmed.size() << std::endl;
		std::cout << "Zombies: " << zombie.size() << std::endl;
		std::cout << std::endl;
	}

	// Zombies attempt to zombify and the alarmed attempt to alarm. If zombies fail, an ignorant person will become alarmed 
	void attempt_bite_and_alarm() {
		std::unordered_map<Alarmed, Location>::iterator itr;
		for (int i = 0; i < locations.size(); i++) {
			// Get citizens by location 
			std::vector<Alarmed> alarmed_in_loc = get_keys_by_location(alarmed, locations.at(i));
			std::vector<Ignorant> ignorant_in_loc = get_keys_by_location(ignorant, locations.at(i));

			// Each alarmed person will alarm one ignorant person 
			int alarmed_ignorants = 0;
			int stop_flag = alarmed_in_loc.size();
			for (Ignorant ig : ignorant_in_loc) {
				if (alarmed_ignorants == stop_flag) {
					break;
				}
				Alarmed a = Alarmed(ig.get_age());
				alarmed.insert(std::make_pair(a, locations.at(i)));
				ignorant.erase(ig); // Remove ignorant and "move" it to alarmed
				alarmed_ignorants++;
			}

			// Each zombie has a chance of biting someone, if there is as many or more citizens then zombies
			std::vector<Zombie> zombies_in_loc = get_keys_by_location(zombie, locations.at(i));
			for (int j = 0; j < zombies_in_loc.size(); j++) {
				if (alarmed_in_loc.size() > 0 && ignorant_in_loc.size() > 0) {
					int alarmed_or_ignorant = rand() % 2; // Choosing between whether the zombie bites an alarmed or an ignorant
					if (alarmed_or_ignorant == 0) { // Try to bite a random alarmed
						int alarmed_index = rand() % (alarmed_in_loc.size()); // a random index
						double probability = 100 * ((double)rand() / (double)RAND_MAX) / 100;
						if (probability < ALARMED_BITTEN_RATIO) { 
							Zombie z = Zombie();
							zombie.insert(std::make_pair(z, locations.at(i)));
							alarmed.erase(alarmed_in_loc.at(alarmed_index));
						}
					}
					else { // Try to bite a random ignorant
						int ignorant_index = rand() % (ignorant_in_loc.size()); // a random index
						double probability = 100 * ((double)rand() / (double)RAND_MAX) / 100;
						if (probability < IGNORANT_BITTEN_RATIO) {
							Zombie z = Zombie();
							zombie.insert(std::make_pair(z, locations.at(i)));
							ignorant.erase(ignorant_in_loc.at(ignorant_index));
						}
						else { // If the bite fails, that ignorant is now alarmed
							Ignorant ig = ignorant_in_loc.at(ignorant_index);
							Alarmed a = Alarmed(ig.get_age());
							ignorant.erase(ig);
							alarmed.insert(std::make_pair(a, locations.at(i)));
						}
					}
				}
				else if (alarmed_in_loc.size() > 0 && ignorant_in_loc.size() == 0) {
					int alarmed_index = rand() % (alarmed_in_loc.size()); // a random index
					double probability = 100 * ((double)rand() / (double)RAND_MAX) / 100;
					if (probability < ALARMED_BITTEN_RATIO) {
						Zombie z = Zombie();
						zombie.insert(std::make_pair(z, locations.at(i)));
						alarmed.erase(alarmed_in_loc.at(alarmed_index));
					}
				}
				else if (ignorant_in_loc.size() > 0 && alarmed_in_loc.size() == 0) {
					int ignorant_index = rand() % (ignorant_in_loc.size()); // a random index
					double probability = 100 * ((double)rand() / (double)RAND_MAX) / 100;
					if (probability < IGNORANT_BITTEN_RATIO) {
						Zombie z = Zombie();
						zombie.insert(std::make_pair(z, locations.at(i)));
						ignorant.erase(ignorant_in_loc.at(ignorant_index));
					}
					else { // If the bite fails, that ignorant is now alarmed
						Ignorant ig = ignorant_in_loc.at(ignorant_index);
						Alarmed a = Alarmed(ig.get_age());
						ignorant.erase(ig);
						alarmed.insert(std::make_pair(a, locations.at(i)));
					}
				}
			}
		}
	}
	
	// Gets Alarmed citizens by their location 
	std::vector<Alarmed> get_keys_by_location(std::unordered_map<Alarmed, Location> map, Location loc) {
		std::unordered_map<Alarmed, Location>::iterator itr;
		std::vector<Alarmed> keys;
		for (itr = map.begin(); itr != map.end(); ++itr) {
			if (itr->second == loc) {
				keys.push_back(itr->first);
			}
		}
		return keys;
	}

	// Gets Ignorant citizens by their location 
	std::vector<Ignorant> get_keys_by_location(std::unordered_map<Ignorant, Location> map, Location loc) {
		std::unordered_map<Ignorant, Location>::iterator itr;
		std::vector<Ignorant> keys;
		for (itr = map.begin(); itr != map.end(); ++itr) {
			if (itr->second == loc) {
				keys.push_back(itr->first);
			}
		}
		return keys;
	}

	// Gets zombies by location 
	std::vector<Zombie> get_keys_by_location(std::unordered_map<Zombie, Location> map, Location loc) {
		std::unordered_map<Zombie, Location>::iterator itr;
		std::vector<Zombie> keys;
		for (itr = map.begin(); itr != map.end(); ++itr) {
			if (itr->second == loc) {
				keys.push_back(itr->first);
			}
		}
		return keys;
	}

	// Populates the tree in such a way that matches the desired layout 
	void populate_tree() {
		root->insert(root, 2);
		root->insert(root, 1);
		root->insert(root, 5);
		root->insert(root, 4);
		root->insert(root, 6);
	}

	// controls Ignorant's commute to work 
	void commute_work() {
		std::unordered_map<Ignorant, Location>::iterator itr;
		for (itr = ignorant.begin(); itr != ignorant.end(); ++itr) {
			itr->second = itr->first.get_workplace();
		}
	}

	// controls Ignorant's commute home 
	void commute_home() {
		std::unordered_map<Ignorant, Location>::iterator itr;
		for (itr = ignorant.begin(); itr != ignorant.end(); ++itr) {
			itr->second = itr->first.get_home();
		}
	}

	// Moves the Alarmed and the Zombies from one place to the next 
	void shuffle() {
		// alarmed 
		std::unordered_map<Alarmed, Location>::iterator itr;
		for (itr = alarmed.begin(); itr != alarmed.end(); ++itr) {
			int id = static_cast<int>(itr->second); 
			District<int>* parent = root->search(root, id);
			for (int i = 1; i < itr->first.get_speed(); ++i) {
				int probability = rand() % 3 + 1; 
				switch (probability) {
				case 1:
					itr->second = (Location)parent->data; 
					break;
				case 2: 
					if (parent->left != NULL) {
						itr->second = (Location)parent->left->data;
						break; 
					}
				case 3:
					if (parent->right != NULL) {
						itr->second = (Location)parent->right->data; 
						break;
					}
				default: 
					itr->second = (Location)parent->data; 
					break; 
				}
			}
		}

		// repeat the same for zombies
		std::unordered_map<Zombie, Location>::iterator itr_z;
		for (itr_z = zombie.begin(); itr_z != zombie.end(); ++itr_z) {
			int id = static_cast<int>(itr_z->second);
			District<int>* parent = root->search(root, id);
			for (int i = 1; i < itr->first.get_speed(); ++i) {
				int probability = rand() % 3 + 1;
				switch (probability) {
				case 1:
					itr_z->second = (Location)parent->data;
					break;
				case 2:
					if (parent->left != NULL) {
						itr_z->second = (Location)parent->left->data;
						break;
					}
				case 3:
					if (parent->right != NULL) {
						itr_z->second = (Location)parent->right->data;
						break;
					}
				default:
					itr_z->second = (Location)parent->data;
					break;
				}
			}
		}
	}

	// Returns a random location 
	Location get_random_location() {
		int index = rand() % (locations.size() - 1);
		return locations.at(index);
	}

public:
	// Parameterized constructor that creates the districts and populates them 
	Simulator(int days, int zombies, int denizens, Location loc, double ign_ratio, double alrm_ratio)
		: NUM_DAYS(days), START_ZOMBS(zombies), START_LOC(loc), IGNORANT_BITTEN_RATIO(ign_ratio), ALARMED_BITTEN_RATIO(alrm_ratio) {
		time_of_day = 0;
		days_run = 0;
		int denizens_populated = 0;
		populate_tree();
		root->print(root);
		std::cout << std::endl;

		// create the zombie(s) and place them in the start location
		for (int i = 0; i < zombies; i++) {
			Zombie z = Zombie();
			zombie.insert(std::make_pair(z, loc));
			denizens_populated++;
		}

		do {
			int age = rand() % (99 - 13 + 1) + 13; // Random age between 13 and 99 (inclusive)
			Ignorant ig = Ignorant(age, get_random_location(), get_random_location());
			Location start = ig.get_home();
			ignorant.insert(std::make_pair(ig, start));
			denizens_populated++;
		} while (denizens_populated < denizens);
	}


	// Default constructor that creates the districts and populates them 
	Simulator() : NUM_DAYS(20), START_ZOMBS(1), START_LOC(Location::U_DISTRICT), IGNORANT_BITTEN_RATIO(0.60), ALARMED_BITTEN_RATIO(0.40) {
		time_of_day = 0;
		days_run = 0;
		int denizens_populated = 0;
		populate_tree();
		root->print(root);
		std::cout << std::endl;

		Zombie z = Zombie();
		zombie.insert(std::make_pair(z, Location::U_DISTRICT));
		denizens_populated++;
		do {
			int age = rand() % (99 - 13 + 1) + 13; // Random age between 13 and 99 (inclusive)
			Ignorant ig = Ignorant(age, get_random_location(), get_random_location());
			Location start = ig.get_home();
			ignorant.insert(std::make_pair(ig, start));
			denizens_populated++;
		} while (denizens_populated < 30); // Defaults to 30 denizens in the simulation
	}
	
	// Runs the simulation 
	void run() {
		do {
			if (days_run == NUM_DAYS) {
				std::cout << std::endl;
				std::cout << "SIMULATION ENDED: DAY " << days_run << std::endl;
				print_simulation_report();
				break;
			}
			else {
				tick();

				// Intentionally slows down the program to provide more randomness and allow the user to see the input - temporary 
				Sleep(1000);
			}
		} while (ignorant.size() > 0 || alarmed.size() > 0);
	}
};

#endif 
