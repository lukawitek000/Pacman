#pragma once

#include <cmath>
#include <stdlib.h>
#include <time.h>
// go to point x = 20*30 , y = 0


class Inky : public Ghost{
	
private:
	void findAimInChaseMode(const Player &p, const Blinky &b);
	
public:
	Inky(int x, int y, QWidget * parent = 0);
	void move(const Player &p, const Blinky &b);
};
