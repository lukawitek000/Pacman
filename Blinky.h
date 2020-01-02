#pragma once

#include <cmath>

#include <stdlib.h>
#include <time.h>

// go to point x = 20*30 , y = 0


class Blinky : public Figure{
	
private:
	QPoint aim;
	
	double findPathLength(int x, int y){
		return (sqrt(pow(x-aim.x(), 2) + pow(y-aim.y(), 2)));
	};
	
	void findShortestPath(double pathRight, double pathLeft, double pathUp, double pathDown){
		
		if(pathRight < pathLeft && pathRight < pathUp && pathRight < pathDown){
			dir = RIGHT;
		}
		else if(pathLeft < pathRight && pathLeft < pathUp && pathLeft < pathDown){
			dir = LEFT;
		}
		else if(pathUp < pathRight && pathUp < pathLeft && pathUp < pathDown){
			dir = UP;
		}else if(pathDown < pathRight && pathDown < pathLeft && pathDown < pathUp){
			dir = DOWN;
		}
	};
	
	
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
				image = normalImage;
				aim.setX(600);
				aim.setY(0);
			}else if(Figure::mode == CHASE){
				image = normalImage;
				aim.setX(p.position.x());
				aim.setY(p.position.y());
				//choosePath(boardTable);
			}else if(Figure::mode == FRIGHTENED){
				
				srand(time(NULL));
				flickingGhost();
				//image = frightenedGhost;
				aim.setX(rand() % 600 + 1);
				aim.setY(rand() % 600 + 1);
				
			}
			choosePath(boardTable);
		}else if(mode !=FRIGHTENED){
			image = normalImage;
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
