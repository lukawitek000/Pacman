#pragma once


class Snack : public QWidget{
private:
	
	
	
public:
	QRect snackRect;
	
	Snack(int x, int y, QWidget* parent = 0) :QWidget(parent){
		snackRect = QRect(x+15, y+15, 5, 5);
		
		
		
		
		
	}
	
	void paintSnack(QPainter &painter){
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::yellow);
		painter.drawRect(snackRect);
		
	};
	
	
	
	
	
	
	
};
