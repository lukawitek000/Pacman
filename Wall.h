#pragma once
//class GameBoard;
#include <QPainter>
#include <QWidget>

class Wall : public QWidget{
protected:
	QColor color;
public:
	bool isGate;
	QRect wallRect;
	
	Wall(QWidget * parent = 0):QWidget(parent){};
	Wall(int x, int y , QWidget * parent=0);
	void paintWall(QPainter &painter);
};

