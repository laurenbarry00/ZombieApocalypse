#pragma once
#include "pch.h"
#include "Denizen.h"
#include "Walker.h"

#ifndef ALARMED_H_
#define ALARMED_H_

class Alarmed : public Denizen, public Walker {
private: 
	int id;
public: 
	Alarmed(int age) : Denizen(age), Walker(2) {
		id = rand();
	}

	int get_id() const {
		return id;
	}

	bool operator==(const Alarmed &other) const {
		return (id == other.id);
	}
};

namespace std {
	template<>
	struct hash<Alarmed> {
		std::size_t operator()(const Alarmed& a) const {
			using std::size_t;
			using std::hash;
			using std::string;

			size_t hash_output = 0;
			for (size_t i = 0; i < 5; i++) {
				hash_output += (71 * hash_output + i) % 5;
			}
			return hash_output;
		}
	};
}

#endif 