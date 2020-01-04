#include "Figure.h"
#include "Player.h"
#include "Blinky.h"
#include "gameboard.h"



void Blinky::choosePath(){
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
	
	
	
	
	Blinky::Blinky(int x, int y, QWidget * parent) : Figure(parent){
		position = QPoint(x, y);
		normalImage = QImage(QString("%1/Blinky.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		FigureRect = QRect(x, y, GameBoard::sizeOfTile, GameBoard::sizeOfTile);
		std::cout << "creating Blinky" << std::endl;
		aim = QPoint(600, 0);
		//mode = SCATTER;
		dir = LEFT;
		initPosition = position;
		initImage = image;
	};
	
	

	void Blinky::move(const Player &p, int *ghostTimer){
		
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
			choosePath();
		}
		
		if(mode !=FRIGHTENED){
			image = normalImage;
		}else{
			flickingGhost();
			
		}
		//std::cout << "binky dir " << dir << std::endl;
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
		
		if(dir == RIGHT && position.x() >= 690){
			position.setX(0-FigureRect.width());
		}else if(dir == LEFT && position.x() <= 0-FigureRect.width()){
			position.setX(690);
		}
		
		
		
		FigureRect.moveTo(position);
		
		
		
		
	};
	
