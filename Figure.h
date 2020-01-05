#pragma once

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>
#include <QCoreApplication>
#include <QString>
#include <QTransform>


#include <cmath>
#include <stdlib.h>
#include <time.h>

enum direction{
	RIGHT,
	LEFT,
	UP,
	DOWN
};


class Figure : public QWidget{
private:
	bool checkIntersection(int i, QRect temp);
protected:
	QImage image;
	QImage initImage;
	QImage normalImage;
	QPoint initPosition;
	
	virtual void changePosition() = 0;
	void teleportWhenFigureGoOutOfBoard();
public:
	const static int step = 1;
	enum direction dir;
	QPoint position;
	QRect FigureRect;
	
	Figure(QWidget * parent = 0):QWidget(parent){};
	Figure(int x, int y, QWidget * parent = 0);
	//void move(int * timerCount);
	void paintFigure(QPainter &painter);
	bool canMoveRight();
	bool canMoveLeft();
	bool canMoveUp();
	bool canMoveDown();
	void moveToInitPosition();
};

