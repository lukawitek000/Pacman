#include "Figure.h"
#include "ghost.h"
#include "Player.h"
#include "Clyde.h"
#include "gameboard.h"


	

	
	
	
	
	

	
Clyde::Clyde(int x, int y, QWidget * parent) : Ghost(x, y, parent){
		normalImage = QImage(QString("%1/Clyde.png").arg(QCoreApplication::applicationDirPath()));
		image = normalImage;
		std::cout << "creating Clyde" << std::endl;
		aim = QPoint(0, 800);
		initImage = image;
};
	
	

	void Clyde::move(const Player &p){
		//std::cout << "clyde position " << position.x() << " , " << position.y() << std::endl;
		//std::cout << "mode Clyde " << mode <<  std::endl;
		//selectMode();
		if(!getOutFromHome()){
			if(Ghost::mode == SCATTER){
				setScatterAim(0, 800);
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
	
	//image = normalImage;
				aim.setX(p.position.x());
				aim.setY(p.position.y());
				if(findPathLength(position.x(), position.y()) > 8*30){
					aim.setX(p.position.x());
					aim.setY(p.position.y());
					//std::cout << "-----------------------------" <<  std::endl;
				}else{
					aim.setX(0);
					aim.setY(800);
				}
	
	
	
}
