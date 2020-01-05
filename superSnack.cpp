#include "superSnack.h"
#include "gameboard.h"


SuperSnack::SuperSnack(int x, int y, QWidget* parent) : Snack(parent){
	int positionShift = (GameBoard::sizeOfTile - sizeOfSuperSnack)/2;
	snackRect = QRect(x+positionShift, y+positionShift, sizeOfSuperSnack, sizeOfSuperSnack);
	isSuperSnack = true;
	isVisible = true;
	//std::cout << " creating superSnack" << std::endl;
}
