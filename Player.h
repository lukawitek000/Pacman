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

/*
enum direction{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

*/





class Player : public Figure{
private:
	
	QImage pacmanOpened;
	QImage pacmanClosed;
	
	
	void animation(int * timerCount){
		if(*timerCount == 20)
			*timerCount = 0;
		if(*timerCount%20 < 10){
			image = pacmanOpened;
		}else{
			image = pacmanClosed;
		}
		
		
		
	};
public:
	
	Player(int x, int y,QWidget * parent = 0) : Figure(parent){
		dir = RIGHT;
		nextDir = RIGHT;
		position = QPoint(x, y);
		pacmanOpened = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		pacmanClosed = QImage(QString("%1/pacmanClosed.png").arg(QCoreApplication::applicationDirPath()));
		
		
		//image = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		image = pacmanOpened;
		FigureRect = QRect(x, y, size, size);
		//FigureRect = imageOfPlayer->rect();
		std::cout << "creating player" << std::endl;
		//update();
	};
	
	
	
	

	
	
	
	void move(int * timerCount, int boardTable[30][30]){
		QTransform trans;
		//std::cout << "timercount = " << *timerCount << std::endl;
		image = pacmanOpened;
		//std::cout << "dir = " << dir << std::endl;
		//std::cout << "nextDir = " << nextDir << std::endl;
		/*
		if(*timerCount == 20)
			*timerCount = 0;
		if(*timerCount%20 < 10){
			imageOfPlayer = pacmanOpened;
		}else{
			imageOfPlayer = pacmanClosed;
		}
		*/
		//animation(timerCount);
		
		if(dir == RIGHT){
			if(canMoveRight(boardTable)){
				position.setX(position.x() + step);
				animation(timerCount);
			}else{
				*timerCount = 0;
			}
		}else if(dir == LEFT){
			
			if(canMoveLeft(boardTable)){
				position.setX(position.x() - step);
				animation(timerCount);
			}else{
				*timerCount = 0;
			}
			
			trans.rotate(180);
			image = image.transformed(trans);
		}else if(dir == DOWN){
			
			
			if(canMoveDown(boardTable)){
				position.setY(position.y() + step);
				animation(timerCount);
			}else{
				*timerCount = 0;
			}
			trans.rotate(90);
			image = image.transformed(trans);
		}else if(dir == UP){
			
			if(canMoveUp(boardTable)){
				position.setY(position.y() - step);
				animation(timerCount);
			}else{
				*timerCount = 0;
			}
			trans.rotate(270);
			image = image.transformed(trans);
		}
		
		if(nextDir == RIGHT && canMoveRight(boardTable)){
			dir = RIGHT;
		}else if(nextDir == LEFT && canMoveLeft(boardTable)){
			dir = LEFT;
		}else if(nextDir == UP && canMoveUp(boardTable)){
			dir = UP;
		}else if(nextDir == DOWN && canMoveDown(boardTable)){
			dir = DOWN;
		}
		
		//std::cout << "QWidget::width() " << this->width() << std::endl;
		
		
		if(dir == RIGHT && position.x() == 690){
			position.setX(0-FigureRect.width());
		}else if(dir == LEFT && position.x() == 0-FigureRect.width()){
			position.setX(690);
		}
		
		
		FigureRect.moveTo(position);
		
		//update();
		
	};
	


	
	
};




