#include "ghost.h"
#include "Figure.h"
#include "gameboard.h"

#define GATE_X_POSITION 330
#define HOUSE_Y 300
#define HOUSE_LEFT_WALL 270
#define HOUSE_RIGHT_WALL 390

#define REFRESH GameBoard::speed

#define TIME_OF_MODE_SCATTER_MS (7000/REFRESH)
#define TIME_OF_MODE_CHASE_MS (20000/REFRESH)
#define TIME_OF_WHOLE_CYCLE (TIME_OF_MODE_SCATTER_MS + TIME_OF_MODE_CHASE_MS)
#define TIME_OF_MODE_FIGHTENED_MS (5000/REFRESH)
#define TIME_OF_FLICKING_MS (1000/REFRESH)

#define THE_LONGEST_POSSIBLE_PATH 10000  //najlepiej będzie wziąć wymiary ekranu i przekatna
#define APP_WIDHT 600
#define APP_HEIGHT 600



Mode Ghost::mode;
int Ghost::vulnerableCounter = 0;
int Ghost::ghostTimer;

bool Ghost::getOutFromHome(){
	srand(time(NULL));
	if(position.y() == HOUSE_Y && position.x() >= HOUSE_LEFT_WALL && position.x() <= HOUSE_RIGHT_WALL){
		if(position.x() == HOUSE_LEFT_WALL){
			dir = RIGHT;
		}
		if(position.x() == HOUSE_RIGHT_WALL){
			dir = LEFT;
		}
		srand(time(NULL));
		if(Ghost::mode == FRIGHTENED){
			if(position.x() == GATE_X_POSITION && rand()%10==0){
				dir = UP;
			}
		}else{
			srand(time(NULL));
			if(position.x() == GATE_X_POSITION && rand()%2==0){
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
		if(vulnerableCounter > TIME_OF_MODE_FIGHTENED_MS - TIME_OF_FLICKING_MS){
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
		chooseRandomDir();
	}
};


void Ghost::chooseRandomDir(){
	srand(time(NULL));
	int randomDir = rand() % 4;
	dir = static_cast<direction>(randomDir);
	/*switch(randomDir){
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
	}*/
}


void Ghost::selectMode(){
	if(Ghost::mode != FRIGHTENED){
		//std::cout << "TIME_OF_WHOLE_CYCLE & TIME_OF_MODE_SCATTER_MS & REFRESH" << TIME_OF_WHOLE_CYCLE << " " << TIME_OF_MODE_SCATTER_MS << " " <<REFRESH<<std::endl;
		if(Ghost::ghostTimer % TIME_OF_WHOLE_CYCLE < TIME_OF_MODE_SCATTER_MS){ // 700 to 7 sekund
			Ghost::mode = SCATTER;
		}else{
			Ghost::mode = CHASE;
		}
		if(Ghost::ghostTimer == TIME_OF_WHOLE_CYCLE){
			Ghost::ghostTimer = 0;
		}
	}else{
		vulnerableCounter++;
		if(vulnerableCounter == TIME_OF_MODE_FIGHTENED_MS){
			Ghost::mode = SCATTER;
			vulnerableCounter = 0;
			Ghost::ghostTimer = 0;
		}
	}
}


void Ghost::choosePath(){
	double pathRight = THE_LONGEST_POSSIBLE_PATH;
	double pathLeft = THE_LONGEST_POSSIBLE_PATH;
	double pathUp = THE_LONGEST_POSSIBLE_PATH;
	double pathDown = THE_LONGEST_POSSIBLE_PATH;
		
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
	aim.setX(rand() % APP_WIDHT + 1);
	srand(time(NULL));
	aim.setY(rand() % APP_HEIGHT + 1);
}


void Ghost::setScatterAim(int x, int y){
	aim.setX(x);
	aim.setY(y);
}


void Ghost::moveCaughtGhostToHouse(){
	srand(time(NULL));
	position.setX(rand()% (HOUSE_RIGHT_WALL-HOUSE_LEFT_WALL) + HOUSE_LEFT_WALL);
	//position.setX(300);
	position.setY(HOUSE_Y);
	dir = RIGHT;
	FigureRect.moveTo(position);
};

