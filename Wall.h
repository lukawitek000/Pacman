#pragma once
//class GameBoard;
#include <QPainter>
#include <QWidget>

class Wall : public QWidget{
	
	//Q_OBJECT

	
public:
	bool isGate;
	Wall(QWidget * parent = 0):QWidget(parent){};
	
	Wall(int x, int y , QWidget * parent=0);
	
	
	void paintWall(QPainter &painter);

	
	
	
//private:
	QRect wallRect;
	QColor color;
	//QRect wallRectColor;
	
	
	
	
	
};
