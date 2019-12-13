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

//#include "gameboard.h"

//class Gameboard;


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
	
	
	
	
	
	
	Player(int x, int y){
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
		//std::cout << "painterevent" << std::endl;
		
	};
	
	void move(QKeyEvent *event){
		int step = 5;
		QTransform trans;
		//trans.rotate(180);
		imageOfPlayer = imageOfPlayer.transformed(trans);
		//std::cout << "inside move +++++++++++++++++++ " << std::endl;
		if(event->key() == Qt::Key_Down){
			//std::cout << "inside the key press down " << std::endl;
			imageOfPlayer = pacmanOpened;
			trans.rotate(90);
			imageOfPlayer = imageOfPlayer.transformed(trans);
			position.setY(position.y() + step);
		}
		if(event->key() == Qt::Key_Up){
			//std::cout << "inside the key press up " << std::endl;
			imageOfPlayer = pacmanOpened;
			trans.rotate(270);
			imageOfPlayer = imageOfPlayer.transformed(trans);
			position.setY(position.y() - step);
		}
		if(event->key() == Qt::Key_Right && canMoveRight(step)){
			//std::cout << "inside the key press right " << std::endl;
			imageOfPlayer = pacmanOpened;
			position.setX(position.x() + step);
		}
		if(event->key() == Qt::Key_Left){
			//std::cout << "inside the key press left " << std::endl;
			imageOfPlayer = pacmanOpened;
			position.setX(position.x() - step);
			trans.rotate(180);
			imageOfPlayer = imageOfPlayer.transformed(trans);
		}
		playerRect.moveTo(position);
		
		
		//update();
		
	};
	
	
	bool canMoveRight(int step);
	/*{
		std::cout << "canMoveRight" << Gameboard::getBoardTableValueAt(position.x()+step, position.y())  << std::endl;
		//if(Gameboard::getBoardTableValueAt(position.x()+step, position.y()) == 1)
		//	return false;
		return true;
		
	};
	*/
	
	
	
	
	
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




