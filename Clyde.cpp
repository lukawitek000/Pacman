#include "Figure.h"
#include "Player.h"
#include "Clyde.h"
#include "gameboard.h"


	
	void Clyde::choosePath(){
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

	
	
	
	
	

	
	Clyde::Clyde(int x, int y, QWidget * parent) : Figure(parent){
		position = QPoint(x, y);
		normalImage = QImage(QString("%1/Clyde.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		FigureRect = QRect(x, y, GameBoard::sizeOfTile, GameBoard::sizeOfTile);
		std::cout << "creating Clyde" << std::endl;
		aim = QPoint(0, 800);
		//mode = SCATTER;
		dir = LEFT;
		initPosition = position;
		initImage = image;
	};
	
	

	void Clyde::move(const Player &p, int *ghostTimer){
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
	

