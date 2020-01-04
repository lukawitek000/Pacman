#include "Wall.h"
#include "gameboard.h"




Wall::Wall(int x, int y , QWidget * parent): QWidget(parent){
		wallRect = QRect(x, y, GameBoard::sizeOfTile, GameBoard::sizeOfTile);
		color  = Qt::blue;
		isGate = false;
		//wallRectColor = QRect(x+2, y+2, sizeX-4, sizeY - 4);
	}
	
	
	void Wall::paintWall(QPainter &painter){
		painter.setPen(Qt::NoPen);
		painter.setBrush(color);
		painter.drawRect(wallRect);
	}
