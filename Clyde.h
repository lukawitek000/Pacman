#pragma once


#include <stdlib.h>
#include <time.h>
// go to point x = 20*30 , y = 0


class Clyde : public Figure{
	
private:

	
	void choosePath();
	
	
	
	
	
	
public:
	
	Clyde(int x, int y, QWidget * parent = 0);
	
	

	void move(const Player &p, int *ghostTimer);
	
	
	
};
