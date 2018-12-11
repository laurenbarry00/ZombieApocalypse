// reading a text file
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	string line;
	ifstream myfile("resident.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file" << endl;

	return 0;
}