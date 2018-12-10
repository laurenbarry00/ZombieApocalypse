#pragma once
#include <string>

#ifndef DISTRICT_H_
#define DISTRICT_H_

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