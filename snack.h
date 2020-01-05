#pragma once

#include <QWidget>
#include <QRect>
#include <QPainter>



class Snack : public QWidget{
private:
	const static int sizeOfSnack = 4;
	
public:
	QRect snackRect;
	bool isSuperSnack;
	bool isVisible;
	
	Snack(QWidget* parent = 0):QWidget(parent){};
	Snack(int x, int y, QWidget* parent = 0);
	void paintSnack(QPainter &painter);

};
