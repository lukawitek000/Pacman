#include "Gate.h"
#include "gameboard.h"


Gate::Gate(int x, int y, QWidget * parent): Wall(parent){
	wallRect = QRect(x, y, GameBoard::sizeOfTile, highOfGate);
	color = Qt::gray;
	isGate = true;
};

