#include "snack.h"
#include "gameboard.h"



Snack::Snack(int x, int y, QWidget* parent) :QWidget(parent){
	int positionShift = (GameBoard::sizeOfTile - sizeOfSnack)/2;
	snackRect = QRect(x+positionShift, y+positionShift, sizeOfSnack, sizeOfSnack);
	isSuperSnack = false;
	isVisible = true;
}


void Snack::paintSnack(QPainter &painter){
	if(isVisible){
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::yellow);
		painter.drawRect(snackRect);
	}
};

