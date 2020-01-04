#pragma once 


//PACMAN BOARD
#include <QWidget>
#include <QGridLayout>
#include <QImage>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <QPushButton>



#include "Wall.h" 
#include "Gate.h"
#include "Figure.h"
#include "Player.h"

#include "snack.h"
#include "superSnack.h" 
#include "lcdScore.h"


#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h" 
#include "Pinky.h"
//class GameBoard;



class GameBoard : public QWidget{ 
	 
	Q_OBJECT
	
private: 
	
	
	void readTheBoard();
	void createButtons();
	void createLCDDisplays();
	void createLayout();
	void createBackground();
	
	void eatingSnacks();
	void checkIfPlayerWon();
	
	
	void paintText(QPainter &painter);
	
	void getDirectionForPlayer(QKeyEvent *event);
	void checkContactPlayerWithGhost();
	void movingOfFigures();
	
	Blinky *blinky;
	Inky *inky;
	Clyde *clyde;
	Pinky *pinky;
	
	Player *player; 
	
	
	QPoint playerInit;
	QPoint blinkyInit;
	QPoint inkyInit;
	QPoint pinkyInit;
	QPoint clydeInit;
	
	
	
	
	QVector<Snack*> snacks;
	static QVector<Wall*> walls; 
	
	
	
	
	Gate *gate;
	
	int timerCount; 
	
	bool gameOver;
	bool win;
	bool dead;
	
	int ghostTimer;
	
	QTimer *timer;
	
	int speed = 9 	;
	
	LCDScore * score;  
	LCDScore * lives;
	
	QImage board;
	QGridLayout *gridLayout;
	QGridLayout *layout;
	QGridLayout *buttonLayout;
	
	void init();
	 
private slots:
	void move(); 
	void newGame();  
	
	 
	
public: 
	const static int sizeOfTile = 30; 
	const static int heightOfLCD = 140;
	//static int h;
	
	
	
	
	GameBoard(QWidget *parent  = 0);
	
	static int sizeOfWalls(){
		return walls.size();
	}
	static Wall * getWall(int i){
		return walls[i];
	}
	
protected:  
	
	void paintEvent(QPaintEvent* /*event*/);
	void keyPressEvent(QKeyEvent *event);

	
signals:
	void timeout();
	void collect(int);
	void die();
	
	
};
