#include "Figure.h"
#include "ghost.h"
#include "Player.h"
#include "Blinky.h"
#include "gameboard.h"



Blinky::Blinky(int x, int y, QWidget * parent) : Ghost(x, y, parent){
	normalImage = QImage(QString("%1/img/Blinky.png").arg(QCoreApplication::applicationDirPath()));
	image = normalImage;
	std::cout << "creating Blinky" << std::endl;
	aim = QPoint(scatterXAim, scatterYAim);
	initImage = image;
}


void Blinky::move(const Player &p){
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
}


void Blinky::findAimInChaseMode(const Player &p){
	aim.setX(p.position.x());
	aim.setY(p.position.y());
}

