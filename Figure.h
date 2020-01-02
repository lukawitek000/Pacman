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


class Figure : public QWidget{
	
protected:
	 
	
	QImage image;
	QImage frightenedGhost = QImage(QString("%1/vulnerableGost.png").arg(QCoreApplication::applicationDirPath()));
	QImage frightenedGhostWhite = QImage(QString("%1/vulnerableGhostWhite.png").arg(QCoreApplication::applicationDirPath()));
	
	
	QImage initImage;
	
	
	int size = 30;
	QImage normalImage;
	
	
	
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
	
	
	void move(int * timerCount, int boardTable[30][30]);
	void paintFigure(QPainter &painter);
	
	bool canMoveRight(int boardTable[30][30]);
	
	bool canMoveLeft(int boardTable[30][30]);
	
	bool canMoveUp(int boardTable[30][30]);
	bool canMoveDown(int boardTable[30][30]);
	
	void moveToInitPosition(){
		position = initPosition;
		image = initImage;
		FigureRect.moveTo(position);
	};
	
	
	
	
	
};
