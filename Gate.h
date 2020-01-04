#pragma once
#include "Wall.h"

class Gate : public Wall{
private:
	const static int highOfGate;
	
public:
	Gate(int x, int y, QWidget * parent=0);
	
};
