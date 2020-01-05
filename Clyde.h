#pragma once


#include <stdlib.h>
#include <time.h>
// go to point x = 20*30 , y = 0


class Clyde : public Ghost{
	
private:
	void findAimInChaseMode(const Player &p);
	const static int scatterXAim = 0;
	const static int scatterYAim = 800;
	const static int safeDistanceFromPlayerInTiles = 8;
public:
	Clyde(int x, int y, QWidget * parent = 0);
	void move(const Player &p);
};
