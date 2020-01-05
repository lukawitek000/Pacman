#include "Figure.h"
#include "Player.h"
#include "gameboard.h"


#include <iostream>



int Player::playerTimer;

Player::Player(int x, int y,QWidget * parent) : Figure(x, y, parent){
	nextDir = RIGHT;
	pacmanOpened = QImage(QString("%1/img/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
	pacmanClosed = QImage(QString("%1/img/pacmanClosed.png").arg(QCoreApplication::applicationDirPath()));
	image = pacmanOpened;
	std::cout << "creating player" << std::endl;
	initImage = image;
};


void Player::animation(){
	if(Player::playerTimer == 20)
		Player::playerTimer = 0;
	if(Player::playerTimer%20 < 10){
		image = pacmanOpened;
	}else{
		image = pacmanClosed;
	}
};


void Player::move(){
	changePosition();
	if(nextDir == RIGHT && canMoveRight()){
		dir = RIGHT;
	}else if(nextDir == LEFT && canMoveLeft()){
		dir = LEFT;
	}else if(nextDir == UP && canMoveUp()){
		dir = UP;
	}else if(nextDir == DOWN && canMoveDown()){
		dir = DOWN;
	}
	teleportWhenFigureGoOutOfBoard();
	FigureRect.moveTo(position);
};


void Player::changePosition(){
	QTransform trans;
	image = pacmanOpened;
	if(dir == RIGHT){
		if(canMoveRight()){
			position.setX(position.x() + step);
			animation();
		}else{
			Player::playerTimer = 0;
		}
	}else if(dir == LEFT){
		if(canMoveLeft()){
			position.setX(position.x() - step);
			animation();
		}else{
			Player::playerTimer = 0;
		}
		trans.rotate(180);
		image = image.transformed(trans);
	}else if(dir == DOWN){
		if(canMoveDown()){
			position.setY(position.y() + step);
			animation();
		}else{
			Player::playerTimer = 0;
		}
		trans.rotate(90);
		image = image.transformed(trans);
	}else if(dir == UP){
		if(canMoveUp()){
			position.setY(position.y() - step);
			animation();
		}else{
			Player::playerTimer = 0;
		}
		trans.rotate(270);
		image = image.transformed(trans);
	}
};

