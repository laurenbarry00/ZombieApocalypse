#pragma once
#include "pch.h"
#include "Walker.h"

#ifndef ZOMBIE_H_
#define ZOMBIE_H_

class Zombie : public Walker {
private:
	int id;
public: 
	Zombie() : Walker(1) {
		id = rand();
	}

	int get_id() const {
		return id;
	}

	bool operator==(const Zombie &other) const {
		return (id == other.id);
	}
};

namespace std {
	template<>
	struct hash<Zombie> {
		std::size_t operator()(const Zombie& z) const {
			using std::size_t;
			using std::hash;
			using std::string;

			size_t hash_output = 0;
			for (size_t i = 0; i < 5; i++) {
				hash_output += (71 * hash_output + i) % 5;
			}
			return hash_output;;
		}
	};
}

#endif 