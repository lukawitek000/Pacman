#pragma once


class Snack : public QWidget{
private:
	
	
	
public:
	QRect snackRect;
	
	Snack(int x, int y, QWidget* parent = 0) :QWidget(parent){
		snackRect = QRect(x+10, y+10, 10, 10);
		
		
		
		
		
	}
	
	void paintSnack(QPainter &painter){
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::blue);
		painter.drawRect(snackRect);
		
	};
	
	
	
	
	
	
	
};
