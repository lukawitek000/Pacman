#include "Figure.h"
#include "ghost.h"
#include "Player.h"
#include "Pinky.h"
#include "gameboard.h"



Pinky::Pinky(int x, int y, QWidget * parent) : Ghost(x, y, parent){
	normalImage = QImage(QString("%1/pinky.png").arg(QCoreApplication::applicationDirPath()));
	image = normalImage;
	std::cout << "creating Pinky" << std::endl;
	aim = QPoint(scatterXAim, scatterYAim);
	initImage = image;
};


void Pinky::move(const Player &p){
	if(!getOutFromHome()){
		if(Ghost::mode == SCATTER){
			setScatterAim(scatterXAim, scatterYAim);
		}else if(Ghost::mode == CHASE){
			findAimInChaseMode(p);
		}else if(Ghost::mode == FRIGHTENED){
			findRandomAim();
		}
		choosePath();
	}
	setImage();
	changePosition();
	teleportWhenFigureGoOutOfBoard();
	FigureRect.moveTo(position);
};


void Pinky::findAimInChaseMode(const Player &p){
	if(p.dir == RIGHT){
		aim.setX(p.position.x() + numberOfTilesInFrontOfThePlayer * GameBoard::sizeOfTile);
		aim.setY(p.position.y());
	}else if(p.dir == LEFT){
		aim.setX(p.position.x() - numberOfTilesInFrontOfThePlayer * GameBoard::sizeOfTile);
		aim.setY(p.position.y());
	}else if(p.dir == UP){
		aim.setX(p.position.x());
		aim.setY(p.position.y() - numberOfTilesInFrontOfThePlayer * GameBoard::sizeOfTile);
	}else if(p.dir == DOWN){
		aim.setX(p.position.x());
		aim.setY(p.position.y() + numberOfTilesInFrontOfThePlayer * GameBoard::sizeOfTile);
	}
}

