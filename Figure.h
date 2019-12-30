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

#include <QElapsedTimer>

enum direction{
	RIGHT,
	LEFT,
	UP,
	DOWN
};


enum Mode{
	SCATTER,
	FRIGHTENED, 
	CHASE
	
	
};


class Figure : public QWidget{
	
protected:
	 
	QPoint position;
	QImage image;
	Mode mode;

	int size = 30;
	int step = 1;
	
	
public:
	enum direction dir;
	enum direction nextDir;
	
	QRect FigureRect;
	
	Figure(QWidget * parent = 0) : QWidget(parent){};
	
	
	virtual void move(int * timerCount, int boardTable[30][30]) = 0;
	void paintFigure(QPainter &painter);
	
	bool canMoveRight(int boardTable[30][30]);
	
	bool canMoveLeft(int boardTable[30][30]);
	
	bool canMoveUp(int boardTable[30][30]);
	bool canMoveDown(int boardTable[30][30]);
	
	
	
	
	
	
};
