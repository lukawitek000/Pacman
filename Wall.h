#pragma once


#include <QWidget>

class Wall : public QWidget{
	
	//Q_OBJECT
	
public:
	Wall(int x, int y, int sizeX, int sizeY , QWidget * parent=0): QWidget(parent){
		wallRect = QRect(x, y, sizeX, sizeY);
		
	};
	
	
	void paintWall(QPainter &painter){
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::red);
		painter.drawRect(wallRect);
		//painter.drawImage(playerRect, imageOfPlayer);
		//std::cout << "painterevent" << std::endl;
	};

	
	
	
private:
	QRect wallRect;
	
	
	
	
	
	
};
