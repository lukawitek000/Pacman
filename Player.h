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
	
	
	
	
	
	Player(int x, int y){
		dir = RIGHT;
		position = QPoint(x, y);
		pacmanOpened = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		pacmanClosed = QImage(QString("%1/pacmanClosed.png").arg(QCoreApplication::applicationDirPath()));
		
		
		//imageOfPlayer = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		imageOfPlayer = pacmanOpened;
		playerRect = QRect(x, y, 30, 30);
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
	
	/*
	void moving(int boardTable[30][30]){
		bool con = true;
		int step;
		QElapsedTimer timer;
		timer.start();
		do{
		step = 5;
		if(dir == RIGHT){
			if(canMoveRight(boardTable)){
				position.setX(position.x() + step);
				con = true;
			}else{
				con = false;
			}
		}else if(dir == LEFT){
			if(canMoveLeft(boardTable)){
				position.setX(position.x() - step);
				con = true;
			}else{
				con = false;
			}
		}else if(dir == DOWN){
			if(canMoveDown(boardTable)){
				position.setY(position.y() + step);
				con = true;
			}else{
				con = false;
			}
		}else if(dir == UP){
			if(canMoveUp(boardTable)){
				position.setY(position.y() - step);
				con = true;
			}else{
				con = false;
			}
		}
		
		playerRect.moveTo(position);
		std::cout << "MMOVINGGGG" << std::endl;
		if(timer.restart() > 100){
			update();
			repaint();
		}
		//QThread::msleep(10);
		}while(con);
	};
	
	*/
	
	
	void move(QKeyEvent *event, int boardTable[30][30]){
		int step = 5;
		QTransform trans;
		//trans.rotate(180);
		imageOfPlayer = imageOfPlayer.transformed(trans);
		//std::cout << "inside move +++++++++++++++++++ " << std::endl;
		if(event->key() == Qt::Key_Down){
			imageOfPlayer = pacmanOpened;
			trans.rotate(90);
			imageOfPlayer = imageOfPlayer.transformed(trans);
			
			if(canMoveDown(boardTable)){
				//std::cout << "inside the key press down " << std::endl;
				//dir = DOWN;
				position.setY(position.y() + step);
			}
		}
		if(event->key() == Qt::Key_Up){
			imageOfPlayer = pacmanOpened;
			trans.rotate(270);
			imageOfPlayer = imageOfPlayer.transformed(trans);
			if(canMoveUp(boardTable)){
			//std::cout << "inside the key press up " << std::endl;
			//	dir = UP;
				position.setY(position.y() - step);
			}
		}
		if(event->key() == Qt::Key_Right){
			imageOfPlayer = pacmanOpened;
			if(canMoveRight(boardTable)){
			//std::cout << "inside the key press right " << std::endl;
				//dir = RIGHT;
				position.setX(position.x() + step);
			}
		}
		if(event->key() == Qt::Key_Left){
			imageOfPlayer = pacmanOpened;
			trans.rotate(180);
			imageOfPlayer = imageOfPlayer.transformed(trans);
			if(canMoveLeft(boardTable)){
				//std::cout << "inside the key press left " << std::endl;
				//dir = LEFT;
				position.setX(position.x() - step);
			}
		}
		
		//moving(boardTable);
		/*
		if(dir == RIGHT){
			position.setX(position.x() + step);
		}else if(dir == LEFT){
			position.setX(position.x() - step);
		}else if(dir == DOWN){
			position.setY(position.y() + step);
		}else if(dir == UP){
			position.setY(position.y() - step);
		}*/
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




