#pragma once

#ifndef WALKER_H_
#define WALKER_H_

class Walker {
private: 
	int move_speed; 
public: 
	Walker(int speed) : move_speed(speed) {}
	int get_speed(); 
};
#endif 