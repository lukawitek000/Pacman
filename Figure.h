#pragma once

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>
#include <QCoreApplication>
#include <QString>
#include <QTransform>

#include <QElapsedTimer>

#include <cmath>
#include <stdlib.h>
#include <time.h>

enum direction{
	RIGHT,
	LEFT,
	UP,
	DOWN
};


enum Mode{
	SCATTER,
	FRIGHTENED, 
	CHASE
	
	
};
//class GameBoard; 	

class Figure : public QWidget{
private:
	bool checkIntersection(int i, QRect temp);
protected:
	 
	
	QImage image;
	QImage frightenedGhost = QImage(QString("%1/vulnerableGost.png").arg(QCoreApplication::applicationDirPath()));
	QImage frightenedGhostWhite = QImage(QString("%1/vulnerableGhostWhite.png").arg(QCoreApplication::applicationDirPath()));
	
	
	QImage initImage;
	
	
	//int size = 30;
	QImage normalImage;
	
	QPoint aim;
	
	bool getOutFromHome(){
		srand(time(NULL));
		if(position.y() == 300 && position.x() >= 270 && position.x() <=390){
			if(position.x() == 270){
				dir = RIGHT;
			}
			if(position.x() == 390){
				dir = LEFT;
			}
			
			srand(time(NULL));
			if(Figure::mode == FRIGHTENED){
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
	
	
	void flickingGhost(){
		if(vulnerableCounter > 700){
			if(vulnerableCounter % 20 < 7){
				image = frightenedGhost;
			}else{
				image = frightenedGhostWhite;
			}
		}else{
			image = frightenedGhost;
		}
	};
	
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
	
	void selectMode(int *ghostTimer);
	
public:
	static int vulnerableCounter;
	QPoint initPosition;
	
	
	int step = 1;
	static Mode mode;
	enum direction dir;
	enum direction nextDir;
	QPoint position;
	QRect FigureRect;
	
	Figure(QWidget * parent = 0) : QWidget(parent){};
	
	
	void move(int * timerCount);
	void paintFigure(QPainter &painter);
	
	bool canMoveRight();
	
	bool canMoveLeft();
	
	bool canMoveUp();
	bool canMoveDown();
	
	void moveToInitPosition(){
		position = initPosition;
		image = initImage;
		FigureRect.moveTo(position);
	};
	
	
	
	
	
};
