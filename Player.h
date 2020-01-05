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



class Player : public Figure{
private:
	QImage pacmanOpened;
	QImage pacmanClosed;
	
	void animation();
	void changePosition();
public:
	static int playerTimer;
	
	enum direction nextDir;
	Player(int x, int y,QWidget * parent = 0);
	void move();
};




