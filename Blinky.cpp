#include "Figure.h"
#include "ghost.h"
#include "Player.h"
#include "Blinky.h"
#include "gameboard.h"



	
	
	Blinky::Blinky(int x, int y, QWidget * parent) : Ghost(x, y, parent){
		normalImage = QImage(QString("%1/Blinky.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		std::cout << "creating Blinky" << std::endl;
		aim = QPoint(600, 0);
		initImage = image;
	};
	
	

	void Blinky::move(const Player &p){
		
		//selectMode();
		
		if(!getOutFromHome()){
			if(Ghost::mode == SCATTER){
				setScatterAim(600, 0);
			}else if(Ghost::mode == CHASE){
				findAimInChaseMode(p);
			}else if(Ghost::mode == FRIGHTENED){
				findRandomAim();
				
			}
			choosePath();
		}
		
		setImage();
		//std::cout << "binky dir " << dir << std::endl;
		changePosition();
		
		teleportWhenFigureGoOutOfBoard();
		
		
		FigureRect.moveTo(position);
		
		
		
		
	};
	void Blinky::findAimInChaseMode(const Player &p){
		
		//image = normalImage;
				aim.setX(p.position.x());
				aim.setY(p.position.y());
				//choosePath(boardTable);
	}
