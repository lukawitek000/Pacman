#pragma once

#include <cmath>

// go to point x = 20*30 , y = 0


class Inky : public Figure{
	
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
	
	
	
public:
	Inky(int x, int y, QWidget * parent = 0) : Figure(parent){
		position = QPoint(x, y);
		image = QImage(QString("%1/Inky.png").arg(QCoreApplication::applicationDirPath()));
		FigureRect = QRect(x, y, size, size);
		std::cout << "creating Inky" << std::endl;
		aim = QPoint(600, 800);
		mode = CHASE;
		dir = LEFT;
	};
	
	

	void move(const Player &p, const Blinky &b, int boardTable[30][30]){
		
		if(mode == SCATTER){
			image = normalImage;
			choosePath(boardTable);
		}else if(mode == CHASE){
			image = normalImage;
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
			
			
			choosePath(boardTable);
			
		}else if(mode == FRIGHTENED){
			image = frightenedGhost;
		}
		
		
		
		//std::cout << "Inky dir " << dir << std::endl;
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
