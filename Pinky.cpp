#include "Figure.h"
#include "Player.h"
#include "Pinky.h"
#include "gameboard.h"



	void Pinky::choosePath(){
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
	
	
	
	
	
	

	
	
	
	Pinky::Pinky(int x, int y, QWidget * parent) : Figure(parent){
		position = QPoint(x, y);
		normalImage = QImage(QString("%1/pinky.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		FigureRect = QRect(x, y, GameBoard::sizeOfTile, GameBoard::sizeOfTile);
		std::cout << "creating Pinky" << std::endl;
		aim = QPoint(10, 10);
		//mode = SCATTER;
		dir = UP; 
		initPosition = position;
		initImage = image;
	};
	

	void Pinky::move(const Player &p, int *ghostTimer){
		selectMode(ghostTimer);
		//std::cout << "ghostTimer = " << *ghostTimer << std::endl;
		
		//std::cout << "mode = " << mode << std::endl;
		
		if(!getOutFromHome()){
			if(Figure::mode == SCATTER){
				//image = normalImage;
				aim.setX(10);
				aim.setY(10);			
			}else if(Figure::mode == CHASE){
				//image = normalImage;
				if(p.dir == RIGHT){
					aim.setX(p.position.x() + 4*30);
					aim.setY(p.position.y());
				}else if(p.dir == LEFT){
					aim.setX(p.position.x() - 4*30);
					aim.setY(p.position.y());
				}else if(p.dir == UP){
					aim.setX(p.position.x());
					aim.setY(p.position.y() - 4*30);
				}else if(p.dir == DOWN){
					aim.setX(p.position.x());
					aim.setY(p.position.y() + 4*30);
				}
				
				
			}else if(Figure::mode == FRIGHTENED){
				
				//image = frightenedGhost;
				srand(time(NULL));
				aim.setX(rand() % 600 + 1);
				srand(time(NULL));
				aim.setY(rand() % 600 + 1);
			}
			
			choosePath();
		}
		
		if(mode !=FRIGHTENED){
			image = normalImage;
		}else{
			flickingGhost();
		}
		
		

		//	std::cout << "Clyde dir " << dir << std::endl;
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
		
		if(dir == RIGHT && position.x() == 690){
			position.setX(0-FigureRect.width());
		}else if(dir == LEFT && position.x() == 0-FigureRect.width()){
			position.setX(690);
		}
		
		
		FigureRect.moveTo(position);
	};
	
