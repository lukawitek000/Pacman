#pragma once


#include <stdlib.h>
#include <time.h>
// go to point x = 20*30 , y = 0


class Clyde : public Figure{
	
private:
	//QPoint aim;
	/*
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
	*/
	
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
	/*
	void selectMode(int *ghostTimer){
		if(Figure::mode != FRIGHTENED){
			if(*ghostTimer % 2700 < 700){
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
			if(vulnerableCounter == 500){
				Figure::mode = SCATTER;
				vulnerableCounter = 0;
				*ghostTimer = 0;
			}
		}
		
		
	};*/
	
	
	
	
	
	
public:
	
	Clyde(int x, int y, QWidget * parent = 0) : Figure(parent){
		position = QPoint(x, y);
		normalImage = QImage(QString("%1/Clyde.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		FigureRect = QRect(x, y, size, size);
		std::cout << "creating Clyde" << std::endl;
		aim = QPoint(0, 800);
		//mode = SCATTER;
		dir = LEFT;
		initPosition = position;
		initImage = image;
	};
	
	

	void move(const Player &p, int boardTable[30][30], int *ghostTimer){
		//std::cout << "clyde position " << position.x() << " , " << position.y() << std::endl;
		//std::cout << "mode Clyde " << mode <<  std::endl;
		
		
		
		
		selectMode(ghostTimer);
		
		
		if(!getOutFromHome()){
			if(Figure::mode == SCATTER){
				aim.setX(0);
				aim.setY(800);
				//image = normalImage;
			}else if(Figure::mode == CHASE){
				//image = normalImage;
				aim.setX(p.position.x());
				aim.setY(p.position.y());
				if(findPathLength(position.x(), position.y()) > 8*30){
					aim.setX(p.position.x());
					aim.setY(p.position.y());
					//std::cout << "-----------------------------" <<  std::endl;
				}else{
					aim.setX(0);
					aim.setY(800);
				}
				
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
		
	//	std::cout << "Clyde dir " << dir << std::endl;
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
		
		
		
		
		if(dir == RIGHT && position.x() == 690){
			position.setX(0-FigureRect.width());
		}else if(dir == LEFT && position.x() == 0-FigureRect.width()){
			position.setX(690);
		}
		FigureRect.moveTo(position);
	};
	
	
	
	
};
