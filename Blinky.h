#pragma once
// go to point x = 20*30 , y = 0


class Blinky : public Figure{
	
	
public:
	Blinky(int x, int y, QWidget * parent = 0) : Figure(parent){
		position = QPoint(x, y);
		image = QImage(QString("%1/Blinky.png").arg(QCoreApplication::applicationDirPath()));
		FigureRect = QRect(x, y, size, size);
		std::cout << "creating Blinky" << std::endl;
		mode = SCATTER;
	};
	
	

	void move(int * timerCount, int boardTable[30][30]){
		if(mode == SCATTER){
			if(position.x() < 600){
				if(canMoveRight(boardTable)){
					position.setX(position.x() + step);
				}
				
			}
			if(position.y() > 0){
				if(canMoveUp(boardTable)){
					position.setY(position.y() - step);
				}
				
				
				
			}
			
		}
		FigureRect.moveTo(position);
		
		
		
		
	};
	
	
	
	
};
