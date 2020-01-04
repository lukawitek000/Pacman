#pragma once
//#include "superSnack.h"
//#include "normalSnack.h"

class Snack : public QWidget{
private:
	
	
	
public:
	QRect snackRect;
	bool isSuperSnack;
	bool isVisible;
	
	Snack(QWidget* parent = 0):QWidget(parent){};
	
	Snack(int x, int y, QWidget* parent = 0) :QWidget(parent){
		snackRect = QRect(x+13, y+13, 4, 4);
		isSuperSnack = false;
		isVisible = true;
	}
	
	
	
	
	
	void paintSnack(QPainter &painter){
		if(isVisible){
			painter.setPen(Qt::NoPen);
			painter.setBrush(Qt::yellow);
			painter.drawRect(snackRect);
		}
	};

	
};
