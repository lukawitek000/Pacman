#include "Figure.h"
#include "ghost.h"
#include "Player.h"
#include "Clyde.h"
#include "gameboard.h"




Clyde::Clyde(int x, int y, QWidget * parent) : Ghost(x, y, parent){
	normalImage = QImage(QString("%1/Clyde.png").arg(QCoreApplication::applicationDirPath()));
	image = normalImage;
	std::cout << "creating Clyde" << std::endl;
	aim = QPoint(scatterXAim, scatterYAim);
	initImage = image;
};


void Clyde::move(const Player &p){
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


void Clyde::findAimInChaseMode(const Player &p){
	aim.setX(p.position.x());
	aim.setY(p.position.y());
	if(findPathLength(position.x(), position.y()) > safeDistanceFromPlayerInTiles * GameBoard::sizeOfTile){
		aim.setX(p.position.x());
		aim.setY(p.position.y());
	}else{
		aim.setX(scatterXAim);
		aim.setY(scatterYAim);
	}
}

