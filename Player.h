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

/*
enum direction{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

*/





class Player : public Figure{
private:
	
	
	QImage pacmanOpened;
	QImage pacmanClosed;
	
	
	void animation();
	
	void changePosition();
	
	
public:
	enum direction nextDir;
	Player(int x, int y,QWidget * parent = 0);
	void move();
	
};




