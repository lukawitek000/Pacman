#include "Figure.h"

Mode Figure::mode;
int Figure::vulnerableCounter = 0;;


bool Figure::canMoveRight(int boardTable[30][30]){
	if(boardTable[(position.x() + FigureRect.width())/30][position.y()/30] == 1 || boardTable[(position.x() + FigureRect.width())/30][(position.y()+FigureRect.height()-step)/30] == 1)
		return false;
	return true;
	
};


bool Figure::canMoveLeft(int boardTable[30][30]){
	if(boardTable[(position.x()-step)/30][position.y()/30] == 1 || boardTable[(position.x()-step)/30][(position.y()+FigureRect.height()-step)/30] == 1) //dlaczego tu musi być -5 czyli -step a w move right nie????
		return false;
	return true;
};



bool Figure::canMoveUp(int boardTable[30][30]){
	if(boardTable[position.x()/30][(position.y()-step)/30] == 1 || boardTable[(position.x()+FigureRect.width()-step)/30][(position.y()-step)/30] == 1)
		return false;
	return true;
};

bool Figure::canMoveDown(int boardTable[30][30]){
	if(boardTable[position.x()/30][(position.y()+FigureRect.height())/30] == 1 || boardTable[(position.x() + FigureRect.width()-step)/30][(position.y()+FigureRect.height())/30] == 1 || boardTable[position.x()/30][(position.y()+FigureRect.height())/30] == 10 || boardTable[(position.x() + FigureRect.width()-step)/30][(position.y()+FigureRect.height())/30] == 10)
		return false;
	return true;
	
	
};
 

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

	
	
