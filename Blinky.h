#pragma once

#include <cmath>

#include <stdlib.h>
#include <time.h>

// go to point x = 20*30 , y = 0


class Blinky : public Figure{
	
private:
	//QPoint aim;
	
	
	
	
	void choosePath(int boardTable[30][30]){
		double pathRight = 10000;
		double pathLeft = 10000;
		double pathUp = 10000;
		double pathDown = 10000;
		
		if(dir != LEFT && canMoveRight(boardTable)){
			pathRight = findPathLength(position.x()+step, position.y());
		}
		if(dir != RIGHT && canMoveLeft(boardTable)){
			pathLeft = findPathLength(position.x()-step, position.y());
		}
		if(dir != DOWN && canMoveUp(boardTable)){
			pathUp = findPathLength(position.x(), position.y()-step);
		}
		if(dir != UP && canMoveDown(boardTable)){
			pathDown = findPathLength(position.x(), position.y()+step);
		}
		
		findShortestPath(pathRight, pathLeft, pathUp, pathDown);
		
	};

	
	
	
	
public:
	
	
	
	
	Blinky(int x, int y, QWidget * parent = 0) : Figure(parent){
		position = QPoint(x, y);
		normalImage = QImage(QString("%1/Blinky.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		FigureRect = QRect(x, y, size, size);
		std::cout << "creating Blinky" << std::endl;
		aim = QPoint(600, 0);
		//mode = SCATTER;
		dir = LEFT;
		initPosition = position;
		initImage = image;
	};
	
	

	void move(const Player &p, int boardTable[30][30], int *ghostTimer){
		
		selectMode(ghostTimer);
		
		if(!getOutFromHome()){
			if(Figure::mode == SCATTER){
				//image = normalImage;
				aim.setX(600);
				aim.setY(0);
			}else if(Figure::mode == CHASE){
				//image = normalImage;
				aim.setX(p.position.x());
				aim.setY(p.position.y());
				//choosePath(boardTable);
			}else if(Figure::mode == FRIGHTENED){
				
				srand(time(NULL));
				
				//image = frightenedGhost;
				aim.setX(rand() % 600 + 1);
				aim.setY(rand() % 600 + 1);
				
			}
			choosePath(boardTable);
		}
		
		if(mode !=FRIGHTENED){
			image = normalImage;
		}else{
			flickingGhost();
			
		}
		//std::cout << "binky dir " << dir << std::endl;
		if(dir == RIGHT){
			if(canMoveRight(boardTable)){
				position.setX(position.x() + step);
			}
		}else if(dir == LEFT){
			if(canMoveLeft(boardTable)){
				position.setX(position.x() - step);
			}
		}else if(dir == DOWN){
			if(canMoveDown(boardTable)){
				position.setY(position.y() + step);
			}
		}else if(dir == UP){
			if(canMoveUp(boardTable)){
				position.setY(position.y() - step);
			}
		}
		
		if(dir == RIGHT && position.x() >= 690){
			position.setX(0-FigureRect.width());
		}else if(dir == LEFT && position.x() <= 0-FigureRect.width()){
			position.setX(690);
		}
		
		
		
		FigureRect.moveTo(position);
		
		
		
		
	};
	
	
	
	
};
