#pragma once


#include <QWidget>

class Wall : public QWidget{
	
	//Q_OBJECT
	
public:
	Wall(int x, int y, int sizeX, int sizeY , QWidget * parent=0): QWidget(parent){
		wallRect = QRect(x, y, sizeX, sizeY);
		//wallRectColor = QRect(x+2, y+2, sizeX-4, sizeY - 4);
	};
	
	
	void paintWall(QPainter &painter){
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::blue);
		painter.drawRect(wallRect);
		
		//painter.setBrush(Qt::blue);
		
		//painter.drawRect(wallRectColor);
		
		
		//painter.drawImage(playerRect, imageOfPlayer);
		//std::cout << "painterevent" << std::endl;
	};

	
	
	
//private:
	QRect wallRect;
	//QRect wallRectColor;
	
	
	
	
	
};
