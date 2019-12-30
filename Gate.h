#pragma once


class Gate : public Wall{
	
public:
	Gate(int x, int y, QWidget * parent=0): Wall(parent){
		wallRect = QRect(x, y, 30, 10);
		color = Qt::gray;
	};
	
};
