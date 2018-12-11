#pragma once
#include "pch.h"
#include <string>
#include "Location.h"

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
		if (id < node->data) {
			if (node->left == NULL) {
				node->left = new District<T>(id); 
			}
			else {
				node->left = insert(node->left, id);
			}
		}
		else if (id > node->data) {
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

	District* search(District<T>* root, int id) {
		if (root->data == id) {
			return root; 
		}
		if (root->data < id) {
			if (root->right->data == id) {
				return root; 
			}
			else {
				return search(root->right, id); 
			}
		}
		else if (root->data > id) {
			if (root->left->data == id) {
				return root; 
			}
			else {
				return search(root->left, id); 
			}
		}
	}
};

#endif 