#include "Figure.h"
#include "gameboard.h"

Mode Figure::mode;
int Figure::vulnerableCounter = 0;;




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
		//painter.setBrush(Qt::white);
		//painter.drawRect(FigureRect);
		
		
		
		
		painter.drawImage(FigureRect, image);
		//std::cout << "painterevent" << std::endl;
		
	}
	
	
	
	void Figure::selectMode(int *ghostTimer){
		if(Figure::mode != FRIGHTENED){
			if(*ghostTimer % 2700 < 700){ // 700 to 7 sekund
				Figure::mode = SCATTER;
			}else{
				Figure::mode = CHASE;
			}
			if(*ghostTimer == 2700){
				*ghostTimer = 0;
			}
		}else{
			//ghostTimer--;
			vulnerableCounter++;
			if(vulnerableCounter == 2*500){ // 2* a nie 4* bo wywoływane jest 2 razy rzadziej
				Figure::mode = SCATTER;
				vulnerableCounter = 0;
				*ghostTimer = 0;
			}
		}	
	}

	
	
