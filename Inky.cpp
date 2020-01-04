#include "Figure.h"
#include "Player.h"
#include "Blinky.h"
#include "Inky.h"

#include "gameboard.h"


void Inky::choosePath(){
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
	
		
		
	
	
	
	
	

	
	
	Inky::Inky(int x, int y, QWidget * parent) : Figure(parent){
		position = QPoint(x, y);
		normalImage = QImage(QString("%1/Inky.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		FigureRect = QRect(x, y, GameBoard::sizeOfTile, GameBoard::sizeOfTile);
		std::cout << "creating Inky" << std::endl;
		aim = QPoint(600, 800);
		//mode = SCATTER;
		dir = UP;
		initPosition = position;
		initImage = image;
	};
	
	

	void Inky::move(const Player &p, const Blinky &b, int *ghostTimer){
		//std::cout << "inky position " << position.x() << " , " << position.y() << std::endl;
		//std::cout << "inky dir " << dir << std::endl;
		selectMode(ghostTimer);
		
		
		
		if(!getOutFromHome()){
			if(Figure::mode == SCATTER){
				//image = normalImage;
				aim.setX(600);
				aim.setY(800);
			}else if(Figure::mode == CHASE){
				//image = normalImage;
				int x1 = 0;
				int y1 = 0;
				if(p.dir == RIGHT){
					x1 = p.position.x() + 2*30;
					y1 = p.position.y();
				}else if(p.dir == LEFT){
					x1 = p.position.x() - 2*30;
					y1 = p.position.y();
				}else if(p.dir == UP){
					x1 = p.position.x();
					y1 = p.position.y() - 2*30;
				}else if(p.dir == DOWN){
					x1 = p.position.x();
					y1 = p.position.y() + 2*30;
				}
				
				int dx = abs(x1 - b.position.x());
				int dy = abs(y1 - b.position.y());
				
				aim.setX(p.position.x() + dx);
				aim.setY(p.position.y() + dy);

				
			}else if(Figure::mode == FRIGHTENED){
				srand(time(NULL));
				/*if(vulnerableCounter > 700){
					if(vulnerableCounter %10 < 5){
						image = frightenedGhost;
					}else{
						image = frightenedGhostWhite;
					}
				}else{
					image = frightenedGhost;
				}*/
				
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
		
		
		
		//std::cout << "Inky dir " << dir << std::endl;
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
