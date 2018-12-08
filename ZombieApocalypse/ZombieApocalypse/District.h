#pragma once
#include <string>

#ifndef DISTRICT_H_
#define DISTRICT_H_

// I would argue that we don't need this class the way that it's
// currently laid out in the UML because we have the enum. What
// would be useful is changing the design so that District serves as
// the node struct for the BST. I've proposed some basic changes in the 
// uncommented code below based on BST implementation: 

// class District {
// private:
//	std::string name;
//	int alarm_probability; // do we need this? 
// public:
//
// };

template<class T>
struct District {
private: 
	T data; 
	District *left; 
	District *right; 

	District(T value) {
		this->data = value; 
	}
public: 
	void add();
	void print();
	// for our purposes, we probably won't need a delete function. May need a height function
};

#endif 