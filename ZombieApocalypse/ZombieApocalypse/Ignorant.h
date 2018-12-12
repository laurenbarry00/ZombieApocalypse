#pragma once
#include "pch.h"
#include "Denizen.h" 
#include "Location.h" 

#ifndef IGNORANT_H_
#define IGNORANT_H_

class Ignorant : public Denizen {
private: 
	Location work; 
	Location home;
	int id;
public: 
	Ignorant(int age, Location work, Location home) :
		Denizen(age), work(work), home(home), id(rand()) {}

	Location get_home() const { return home; }

	Location get_workplace() const { return work; }

	int get_id() const { return id; }

	// Overloading the == operator to compare one Ignorant person to another
	bool operator==(const Ignorant &other) const {
		return (id == other.id);
	}
};

// Hashing function for the Ignorant Hashmap 
// Required because of the custom type 
namespace std {
	template<>
	struct hash<Ignorant> {
		std::size_t operator()(const Ignorant& ig) const {
			using std::size_t;
			using std::hash;
			using std::string;

			size_t hash_output = 0;
			int id = ig.get_id();
			for (size_t i = 0; i < 5; i++) {
				hash_output += (71 * hash_output + ig.get_id()) % 5;
			}
			return hash_output;
		}
	};
}

#endif 