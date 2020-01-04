#include "ghost.h"
#include "Figure.h"
#include "gameboard.h"


Mode Ghost::mode;
int Ghost::vulnerableCounter = 0;


	bool Ghost::getOutFromHome(){
		srand(time(NULL));
		if(position.y() == 300 && position.x() >= 270 && position.x() <=390){
			if(position.x() == 270){
				dir = RIGHT;
			}
			if(position.x() == 390){
				dir = LEFT;
			}
			
			srand(time(NULL));
			if(Ghost::mode == FRIGHTENED){
				if(position.x() == 330 && rand()%10==0){
					dir = UP;
				}
			}else{
				srand(time(NULL));
				if(position.x() == 330 && rand()%2==0){
					dir = UP;
					
				}
			}
			return true;
		}
		return false;
		
	};
	
	
	void Ghost::setImage(){
		if(mode !=FRIGHTENED){
			image = normalImage;
		}else{
			if(vulnerableCounter > 700){
				if(vulnerableCounter % 20 < 7){
					image = frightenedGhost;
				}else{
					image = frightenedGhostWhite;
				}
			}else{
				image = frightenedGhost;
			}
		
		}
		
		
		
		
	};
	
	double Ghost::findPathLength(int x, int y){
		return (sqrt(pow(x-aim.x(), 2) + pow(y-aim.y(), 2)));
	};
	
	void Ghost::findShortestPath(double pathRight, double pathLeft, double pathUp, double pathDown){
		
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
		}else{
			srand(time(NULL));
			int randomDir = rand() % 4;
			switch(randomDir){
				case 0:
					dir = RIGHT;
					break;
				case 1:
					dir = LEFT;
					break;
				case 2:
					dir = UP;
					break;
				case 3:
					dir = DOWN;
					break;
				default:
					dir = RIGHT;
					break;
			}
		}
	};
	
	
	
	
	




	
	void Ghost::selectMode(){
		if(Ghost::mode != FRIGHTENED){
			if(GameBoard::ghostTimer % 2700 < 700){ // 700 to 7 sekund
				Ghost::mode = SCATTER;
			}else{
				Ghost::mode = CHASE;
			}
			if(GameBoard::ghostTimer == 2700){
				GameBoard::ghostTimer = 0;
			}
		}else{
			//ghostTimer--;
			vulnerableCounter++;
			if(vulnerableCounter == 2*500){ // 2* a nie 4* bo wywoływane jest 2 razy rzadziej
				Ghost::mode = SCATTER;
				vulnerableCounter = 0;
				GameBoard::ghostTimer = 0;
			}
		}	
	}
	
	
	
	void Ghost::choosePath(){
		double pathRight = 10000;
		double pathLeft = 10000;
		double pathUp = 10000;
		double pathDown = 10000;
		
		if(dir != LEFT && canMoveRight()){
			pathRight = findPathLength(position.x()+step, position.y());
		}
		if(dir != RIGHT && canMoveLeft()){
			pathLeft = findPathLength(position.x()-step, position.y());
		}
		if(dir != DOWN && canMoveUp()){
			pathUp = findPathLength(position.x(), position.y()-step);
		}
		if(dir != UP && canMoveDown()){
			pathDown = findPathLength(position.x(), position.y()+step);
		}
		
		findShortestPath(pathRight, pathLeft, pathUp, pathDown);
		
	};
	
	
	void Ghost::changePosition(){
			if(dir == RIGHT){
			if(canMoveRight()){
				position.setX(position.x() + step);
			}
		}else if(dir == LEFT){
			if(canMoveLeft()){
				position.setX(position.x() - step);
			}
		}else if(dir == DOWN){
			if(canMoveDown()){
				position.setY(position.y() + step);
			}
		}else if(dir == UP){
			if(canMoveUp()){
				position.setY(position.y() - step);
			}
		}
	};
	
	
	void Ghost::findRandomAim(){
		srand(time(NULL));
				aim.setX(rand() % 600 + 1);
				srand(time(NULL));
				aim.setY(rand() % 600 + 1);
	}
	
	
	
	void Ghost::setScatterAim(int x, int y){
		
		aim.setX(x);
				aim.setY(y);
				//image = normalImage;
		
		
		
		
	}
	
	
	
	void Ghost::moveCaughtGhostToHouse(){
		srand(time(NULL));
		position.setX(rand()%50 +300);
		position.setY(300);
		FigureRect.moveTo(position);
	};
