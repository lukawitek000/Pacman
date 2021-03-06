#pragma once

#include "Figure.h"
#include "Player.h"
//#include "Blinky.h"

class Blinky;

enum Mode{
	SCATTER,
	FRIGHTENED, 
	CHASE
};


class Ghost:public Figure{
protected:
	QImage frightenedGhost = QImage(QString("%1/img/vulnerableGost.png").arg(QCoreApplication::applicationDirPath()));
	QImage frightenedGhostWhite = QImage(QString("%1/img/vulnerableGhostWhite.png").arg(QCoreApplication::applicationDirPath()));
	QPoint aim;
	
	bool getOutFromHome();
	void setImage();
	double findPathLength(int x, int y);
	void findShortestPath(double pathRight, double pathLeft, double pathUp, double pathDown);
	void chooseRandomDir();
	void choosePath();
	void changePosition();
	void findRandomAim();
	void setScatterAim(int x, int y);
public:
	static void selectMode();
	static int ghostTimer;
	static int vulnerableCounter;
	static Mode mode;
	
	Ghost(QWidget *parent = 0):Figure(parent){};
	Ghost(int x, int y, QWidget *parent = 0):Figure(x, y, parent){};
	virtual void move(const Player &p) = 0;
	virtual void move(const Player &p, const Ghost &b) = 0;
	void moveCaughtGhostToHouse();
};

