#include "Wall.h"
#include "gameboard.h"


Wall::Wall(int x, int y , QWidget * parent): QWidget(parent){
	wallRect = QRect(x, y, GameBoard::sizeOfTile, GameBoard::sizeOfTile);
	color  = Qt::blue;
	isGate = false;
}


void Wall::paintWall(QPainter &painter){
	painter.setPen(Qt::NoPen);
	painter.setBrush(color);
	painter.drawRect(wallRect);
}

