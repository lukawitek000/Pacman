#pragma once




class Ghost:public QWidget{
private:
	QRect ghostRect;
	QImage imageOfGhost;
public:
	Snack(int x, int y, QWidget* parent = 0) :QWidget(parent){
		ghostRect = QRect(x, y, 30, 30);
		//ghostImage = QImage(QString("%1/Pinky.png").arg(QCoreApplication::applicationDirPath()));
		
		
		
		
	}
	
	void paintSnack(QPainter &painter){
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::blue);
		
		//painter.drawImage(ghostRect, imageOfGhost);
		
		painter.drawRect(snackRect);
		
	};
	
	
	
	
	
	
	
};
