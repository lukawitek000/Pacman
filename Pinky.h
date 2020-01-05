#pragma once

#include <cmath>
#include <stdlib.h>
#include <time.h>


class Pinky : public Ghost{
	
private:
	void findAimInChaseMode(const Player &p);
	const static int scatterXAim = 10;
	const static int scatterYAim = 10;
	const static int numberOfTilesInFrontOfThePlayer = 4;
public:
	Pinky(int x, int y, QWidget * parent = 0);
	void move(const Player &p);
	void move(const Player &/*p*/, const Ghost &/*b*/){};
};

