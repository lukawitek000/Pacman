#include "Figure.h"
#include "Player.h"
#include "gameboard.h"


#include <iostream>

using namespace std;

void Player::animation(){
		if(GameBoard::timerCount == 20)
			GameBoard::timerCount = 0;
		if(GameBoard::timerCount%20 < 10){
			image = pacmanOpened;
		}else{
			image = pacmanClosed;
		}
		
		
		
	};

	
	Player::Player(int x, int y,QWidget * parent) : Figure(x, y, parent){
		nextDir = RIGHT;
		pacmanOpened = QImage(QString("%1/pacmanOpened.png").arg(QCoreApplication::applicationDirPath()));
		pacmanClosed = QImage(QString("%1/pacmanClosed.png").arg(QCoreApplication::applicationDirPath()));
		image = pacmanOpened;
		std::cout << "creating player" << std::endl;
		initImage = image;
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
		
		//std::cout << "QWidget::width() " << this->width() << std::endl;
		
		
		teleportWhenFigureGoOutOfBoard();
		
		
		FigureRect.moveTo(position);
		
		//update();
		
	};
	
void Player::changePosition(){
		QTransform trans;
		image = pacmanOpened;
		if(dir == RIGHT){
			if(canMoveRight()){
				position.setX(position.x() + step);
				animation();
			}else{
				GameBoard::timerCount = 0;
			}
		}else if(dir == LEFT){
			
			if(canMoveLeft()){
				position.setX(position.x() - step);
				animation();
			}else{
				GameBoard::timerCount = 0;
			}
			
			trans.rotate(180);
			image = image.transformed(trans);
		}else if(dir == DOWN){
			
			
			if(canMoveDown()){
				position.setY(position.y() + step);
				animation();
			}else{
				GameBoard::timerCount = 0;
			}
			trans.rotate(90);
			image = image.transformed(trans);
		}else if(dir == UP){
			
			if(canMoveUp()){
				position.setY(position.y() - step);
				animation();
			}else{
				GameBoard::timerCount = 0;
			}
			trans.rotate(270);
			image = image.transformed(trans);
		}
	};
