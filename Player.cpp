#include "Figure.h"
#include "Player.h"
#include "gameboard.h"


#include <iostream>

using namespace std;

void Player::animation(int * timerCount){
		if(*timerCount == 20)
			*timerCount = 0;
		if(*timerCount%20 < 10){
			image = pacmanOpened;
		}else{
			image = pacmanClosed;
		}
		
		
		
	};

	
	Player::Player(int x, int y,QWidget * parent) : Figure(parent){
		dir = RIGHT;
		nextDir = RIGHT;
		position = QPoint(x, y);
		pacmanOpened = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		pacmanClosed = QImage(QString("%1/pacmanClosed.png").arg(QCoreApplication::applicationDirPath()));
		step =1 ;
		initPosition = position;
		
		//image = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		image = pacmanOpened;
		FigureRect = QRect(x, y, GameBoard::sizeOfTile, GameBoard::sizeOfTile);
		//FigureRect = imageOfPlayer->rect();
		std::cout << "creating player" << std::endl;
		initImage = image;
		//update();
	};
	

	
	
	
	void Player::move(int * timerCount){
		QTransform trans;
		image = pacmanOpened;
		if(dir == RIGHT){
			if(canMoveRight()){
				position.setX(position.x() + step);
				animation(timerCount);
			}else{
				*timerCount = 0;
			}
		}else if(dir == LEFT){
			
			if(canMoveLeft()){
				position.setX(position.x() - step);
				animation(timerCount);
			}else{
				*timerCount = 0;
			}
			
			trans.rotate(180);
			image = image.transformed(trans);
		}else if(dir == DOWN){
			
			
			if(canMoveDown()){
				position.setY(position.y() + step);
				animation(timerCount);
			}else{
				*timerCount = 0;
			}
			trans.rotate(90);
			image = image.transformed(trans);
		}else if(dir == UP){
			
			if(canMoveUp()){
				position.setY(position.y() - step);
				animation(timerCount);
			}else{
				*timerCount = 0;
			}
			trans.rotate(270);
			image = image.transformed(trans);
		}
		
		if(nextDir == RIGHT && canMoveRight()){
			dir = RIGHT;
		}else if(nextDir == LEFT && canMoveLeft()){
			dir = LEFT;
		}else if(nextDir == UP && canMoveUp()){
			dir = UP;
		}else if(nextDir == DOWN && canMoveDown()){
			dir = DOWN;
		}
		
		//std::cout << "QWidget::width() " << this->width() << std::endl;
		
		
		if(dir == RIGHT && position.x() >= 690){
			position.setX(0-FigureRect.width());
		}else if(dir == LEFT && position.x() <= 0-FigureRect.width()){
			position.setX(690);
		}
		
		
		FigureRect.moveTo(position);
		
		//update();
		
	};
	
