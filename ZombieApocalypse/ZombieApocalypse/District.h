#pragma once
#include "pch.h"
#include <string>

#ifndef DISTRICT_H_
#define DISTRICT_H_

#include <iostream>

template<class T>
struct District { 
public: 
	// data is an id 
	T data; 
	District *left = NULL; 
	District *right = NULL; 

	District(T value) {
		this->data = value;
	}

	District* insert(struct District* node, T id) {
		std::cout << "Hello World" << std::endl; 
		if (id < node->data) {
			std::cout << "Hello Worldf" << std::endl; 
			if (node->left == NULL) {
				node->left = new District<T>(id); 
			}
			else {
				node->left = insert(node->left, id);
			}
		}
		else if (id > node->data) {
			std::cout << "Hello Worlde" << std::endl;
			if (node->right == NULL) {
				node->right = new District<T>(id); 
			}
			else {
				node->right = insert(node->right, id);
			}
		}
		
		return node; 
	}
	void print(District<T>* root) {
		if (!root) return; 
		print(root->left); 
		std::cout << root->data << " ";
		print(root->right); 
	}
	District* search(); 
	// for our purposes, we probably won't need a delete function. May need a height function
};

#endif 