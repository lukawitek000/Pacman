#include "Figure.h"
#include "gameboard.h"

Figure::Figure(int x, int y, QWidget * parent) : QWidget(parent){
	std::cout<<"Figure constructor" << std::endl;
	position = QPoint(x, y);
	dir = RIGHT;
	initPosition = position;
	FigureRect = QRect(x, y, GameBoard::sizeOfTile, GameBoard::sizeOfTile);
};




bool Figure::canMoveRight(){
	QRect temp(FigureRect);
	temp.moveTo(position.x() + step, position.y());
	for(int i=0; i<GameBoard::sizeOfWalls(); i++){
		if(checkIntersection(i, temp)){
		 return false;
		}
		
	}
	return true;
}

bool Figure::canMoveLeft(){
	QRect temp(FigureRect);
	temp.moveTo(position.x() - step, position.y());
	for(int i=0; i<GameBoard::sizeOfWalls(); i++){
		if(checkIntersection(i, temp)){
		 return false;
		}
		
	}
	return true;
}
bool Figure::canMoveUp(){
	QRect temp(FigureRect);
	temp.moveTo(position.x(), position.y()-step);
	for(int i=0; i<GameBoard::sizeOfWalls(); i++){
		if(!(GameBoard::getWall(i)->isGate)){
			if(checkIntersection(i, temp)){
				return false;
			}
		}
		
	}
	return true;
}
bool Figure::canMoveDown(){
	QRect temp(FigureRect);
	temp.moveTo(position.x() , position.y()+ step);
	for(int i=0; i<GameBoard::sizeOfWalls(); i++){
		if(checkIntersection(i, temp)){
			return false;
		}
		
	}
	return true;
}

bool Figure::checkIntersection(int i, QRect temp){
	if(temp.intersects(GameBoard::getWall(i)->wallRect)){
		return true;
	}
	return false;
	
}

void Figure::paintFigure(QPainter &painter){
	painter.setPen(Qt::NoPen);
	painter.drawImage(FigureRect, image);
}

void Figure::teleportWhenFigureGoOutOfBoard(){
	if(dir == RIGHT && position.x() >= 690){
		position.setX(0-FigureRect.width());
	}else if(dir == LEFT && position.x() <= 0-FigureRect.width()){
		position.setX(690);
	}
}

void Figure::moveToInitPosition(){
	position = initPosition;
	image = initImage;
	FigureRect.moveTo(position);
};

