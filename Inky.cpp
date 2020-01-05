#include "Figure.h"
#include "ghost.h"
#include "Player.h"
#include "Blinky.h"
#include "Inky.h"
#include "gameboard.h"


Inky::Inky(int x, int y, QWidget * parent) : Ghost(x, y, parent){
	normalImage = QImage(QString("%1/Inky.png").arg(QCoreApplication::applicationDirPath()));
	image = normalImage;
	std::cout << "creating Inky" << std::endl;
	aim = QPoint(scatterXAim, scatterYAim);
	initImage = image;
};


void Inky::move(const Player &p, const Ghost &b){
	//std::cout << "inky move" << std::endl;
	if(!getOutFromHome()){
		if(Ghost::mode == SCATTER){
			setScatterAim(scatterXAim, scatterYAim);
		}else if(Ghost::mode == CHASE){
			findAimInChaseMode(p, b);
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


void Inky::findAimInChaseMode(const Player &p, const Ghost &b){
	int x1 = 0;
	int y1 = 0;
	if(p.dir == RIGHT){
		x1 = p.position.x() + numberOfTilesInFrontOfThePlayer * GameBoard::sizeOfTile;
		y1 = p.position.y();
	}else if(p.dir == LEFT){
		x1 = p.position.x() - numberOfTilesInFrontOfThePlayer * GameBoard::sizeOfTile;
		y1 = p.position.y();
	}else if(p.dir == UP){
		x1 = p.position.x();
		y1 = p.position.y() - numberOfTilesInFrontOfThePlayer * GameBoard::sizeOfTile;
	}else if(p.dir == DOWN){
		x1 = p.position.x();
		y1 = p.position.y() + numberOfTilesInFrontOfThePlayer * GameBoard::sizeOfTile;
	}
	int dx = abs(x1 - b.position.x());
	int dy = abs(y1 - b.position.y());
	aim.setX(p.position.x() + dx);
	aim.setY(p.position.y() + dy);
}

