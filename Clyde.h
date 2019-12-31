#pragma once

#include <cmath>

// go to point x = 20*30 , y = 0


class Clyde : public Figure{
	
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
	Clyde(int x, int y, QWidget * parent = 0) : Figure(parent){
		position = QPoint(x, y);
		image = QImage(QString("%1/Clyde.png").arg(QCoreApplication::applicationDirPath()));
		FigureRect = QRect(x, y, size, size);
		std::cout << "creating Clyde" << std::endl;
		aim = QPoint(0, 800);
		mode = SCATTER;
		dir = LEFT;
		
	};
	
	

	void move(const Player &p, int boardTable[30][30]){
		//std::cout << "clyde aim " << aim.x() << " , " << aim.y() << std::endl;
		//std::cout << "mode Clyde " << mode <<  std::endl;
		if(mode == SCATTER){
			aim.setX(0);
			aim.setY(800);
			image = normalImage;
			if(position.y() == 300 && position.x() == 330){
				dir = UP;
				mode = CHASE;
			}else{
				choosePath(boardTable);
				
			}
		}else if(mode == CHASE){
			image = normalImage;
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
			choosePath(boardTable);
		}else if(mode == FRIGHTENED){
			image = frightenedGhost;
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
