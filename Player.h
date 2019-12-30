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

//#include "gameboard.h"

//class Gameboard;


enum direction{
	RIGHT,
	LEFT,
	UP,
	DOWN
};







class Player : public QWidget{
private:
	/*
	QRect playerRect;
	QPoint position;
	QImage imageOfPlayer;
	QImage pacmanOpened;// = new QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
	QImage pacmanClosed;// = new QImage(QString("%1/pacmanClosed.png").arg(QCoreApplication::applicationDirPath()));
*/
public:
	QRect playerRect;
	QPoint position;
	QImage imageOfPlayer;
	QImage pacmanOpened;// = new QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
	QImage pacmanClosed;
	enum direction dir;
	int step = 1;
	
	
	
	
	Player(int x, int y, int size){
		dir = RIGHT;
		position = QPoint(x, y);
		pacmanOpened = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		pacmanClosed = QImage(QString("%1/pacmanClosed.png").arg(QCoreApplication::applicationDirPath()));
		
		
		//imageOfPlayer = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		imageOfPlayer = pacmanOpened;
		playerRect = QRect(x, y, size, size);
		//playerRect = imageOfPlayer->rect();
		std::cout << "creating player" << std::endl;
		//update();
	};
	
	void paintPlayer(QPainter &painter){
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::black);
		//painter.drawRect(playerRect);
		
		painter.drawImage(playerRect, imageOfPlayer);
	//	std::cout << "painterevent" << std::endl;
		
	};
	
	

	
	
	
	void move(int * timerCount, int boardTable[30][30]){
		
		QTransform trans;
		//trans.rotate(180);
		//imageOfPlayer = imageOfPlayer.transformed(trans);
		std::cout << "timercount = " << *timerCount << std::endl;
		if(*timerCount == 20)
			*timerCount = 0;
		if(*timerCount%20 < 10){
			imageOfPlayer = pacmanOpened;
		}else{
			imageOfPlayer = pacmanClosed;
		}
		
		
		if(dir == RIGHT && canMoveRight(boardTable)){
			position.setX(position.x() + step);
		}else if(dir == LEFT){
			trans.rotate(180);
			imageOfPlayer = imageOfPlayer.transformed(trans);
			if(canMoveLeft(boardTable)){
				position.setX(position.x() - step);
			}
		}else if(dir == DOWN){
			
			trans.rotate(90);
			imageOfPlayer = imageOfPlayer.transformed(trans);
			if(canMoveDown(boardTable)){
				position.setY(position.y() + step);
			}
		}else if(dir == UP){
			trans.rotate(270);
			imageOfPlayer = imageOfPlayer.transformed(trans);
			if(canMoveUp(boardTable)){
				position.setY(position.y() - step);
			}
		}
		playerRect.moveTo(position);
		
		//update();
		
	};
	
	
	bool canMoveRight(int boardTable[30][30]);
	/*{
		std::cout << "canMoveRight" << Gameboard::getBoardTableValueAt(position.x()+step, position.y())  << std::endl;
		//if(Gameboard::getBoardTableValueAt(position.x()+step, position.y()) == 1)
		//	return false;
		return true;
		
	};
	*/
	
	bool canMoveLeft(int boardTable[30][30]);
	
	bool canMoveUp(int boardTable[30][30]);
	bool canMoveDown(int boardTable[30][30]);
	
	
	
	
protected:
	/*
	void paintEvent(QPaintEvent ){
		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::black);
		//painter.drawRect(playerRect);
		painter.drawImage(playerRect, imageOfPlayer);
		//std::cout << "painterevent" << std::endl;
	};
	*/
	
	
	
	
	
	
	//void keyPressEvent(QKeyEvent *event){
	
	
	
	
};




