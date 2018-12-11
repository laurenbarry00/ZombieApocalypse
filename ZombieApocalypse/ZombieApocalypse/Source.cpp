#include "pch.h"
#include "District.h"

int main() {
	District<int>* root = new District<int>(3); 
	root->insert(root, 1);
	root->insert(root, 6);
	root->insert(root, 2); 
	root->print(root); 
}