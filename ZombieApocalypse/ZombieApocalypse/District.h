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
	// Node structure
	T data; 
	District *left = NULL; 
	District *right = NULL; 

	// Node constructor
	District(T value) {
		this->data = value;
	}

	// Inserts a new District with the given value into the BST 
	District* insert(struct District* node, T id) {
		if (id < node->data) {
			if (node->left == NULL) { // Base case: reached the bottom of the tree
				node->left = new District<T>(id); 
			}
			else {
				// Recursively traces through the left-hand side of the tree 
				node->left = insert(node->left, id);
			}
		}
		else if (id > node->data) {
			if (node->right == NULL) { // Base case: reached the bottom of the tree 
				node->right = new District<T>(id); 
			}
			else {
				// Recursively traces through the right-hand side of the tree 
				node->right = insert(node->right, id);
			}
		}
		return node; 
	}
	
	// Prints the BST as a string of space-separated entries 
	void print(District<T>* root) {
		if (!root) return; 
		print(root->left); 
		std::cout << root->data << " ";
		print(root->right); 
	}

	// Traces through the binary tree to return the parent of the query
	District* search(District<T>* root, int id) {
		// Base case 
		if (root->data == id) {
			return root; 
		}
		// If the child's data matches the query, return the parent 
		if (root->right->data == id || root->left->data == id) {
			return root; 
		}
		else if (root->data < id) {
			return search(root->right, id); 
		}
		else if (root->data > id) {
			return search(root->left, id); 
		}
	}
};

#endif 