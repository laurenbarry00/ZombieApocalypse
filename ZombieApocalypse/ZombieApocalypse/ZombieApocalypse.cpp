
#include "pch.h"
#include "Simulator.h"
#include <time.h>
using namespace std;

int main() {
	srand(time(nullptr));
	Simulator sim = Simulator();
	sim.run();
	return 0;
}