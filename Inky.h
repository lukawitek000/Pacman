#pragma once

#include <cmath>
#include <stdlib.h>
#include <time.h>

class Inky : public Ghost{
private:
	void findAimInChaseMode(const Player &p, const Ghost &b);
	const static int scatterXAim = 600;
	const static int scatterYAim = 800;
	const static int numberOfTilesInFrontOfThePlayer = 2;
public:
	Inky(int x, int y, QWidget * parent = 0);
	void move(const Player &p, const Ghost &b);
	void move(const Player & /*p*/){};
};

