#pragma once

#include <cmath>

// go to point x = 20*30 , y = 0


class Pinky : public Figure{
	
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
		}else{
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
	
	QImage normalImage;
	
public:
	Pinky(int x, int y, QWidget * parent = 0) : Figure(parent){
		position = QPoint(x, y);
		normalImage = QImage(QString("%1/pinky.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		FigureRect = QRect(x, y, size, size);
		std::cout << "creating Pinky" << std::endl;
		aim = QPoint(10, 10);
		mode = CHASE;
		dir = LEFT;
	};
	
	

	void move(const Player &p, int boardTable[30][30]){
		
		if(mode == SCATTER){
			image = normalImage;
			aim.setX(10);
			aim.setY(10);
		}else if(mode == CHASE){
			image = normalImage;
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
			//choosePath(boardTable);
		}else if(mode == FRIGHTENED){
			image = frightenedGhost;
			
			
			
			
			
		}
		choosePath(boardTable);
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
