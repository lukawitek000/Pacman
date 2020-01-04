#pragma once

#include <cmath>

#include <stdlib.h>
#include <time.h>

// go to point x = 20*30 , y = 0


class Blinky : public Ghost{
	
private:
	void findAimInChaseMode(const Player &p);

public:
	//Blinky(QWidget * parent = 0): Ghost(parent){};
	
	Blinky(int x, int y, QWidget * parent = 0);
	
	void move(const Player &p);

};
