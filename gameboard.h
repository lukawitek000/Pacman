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



#define BOARD_WIDTH 23
#define BOARD_HEIGHT 22
#define SIZE_OF_SIGNLE_ELEMENT 30
#define WIDTH_OF_WINDOW 30*23
#define HEIGHT_OF_WINDOW 22*30 + 100




#include "Figure.h"
#include "Player.h"
#include "Wall.h" 
#include "snack.h"
#include "superSnack.h" 
#include "lcdScore.h"
#include "Gate.h"

#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h" 
#include "Pinky.h"



class GameBoard : public QWidget{ 
	 
	Q_OBJECT
	
private: 
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
	
	
	
	QVector<Wall*> walls;
	QVector<Snack*> snacks;
	QVector<SuperSnack*> superSnacks;   
	Gate *gate;
	int w; 
	int h;
	int timerCount; 
	
	bool gameOver;
	bool win;
	bool dead;
	
	int ghostTimer;
	
	QTimer *timer;
	
	int speed = 10;
	
	LCDScore * score;  
	LCDScore * lives;
	
	QImage board;
	QGridLayout *gridLayout;
	QGridLayout *layout;
	
	void init();
	 
private slots:
	void movePacman(); 
	void newGame();  
	
	 
	
public: 
	int boardTable[30][30];
	
	GameBoard(QWidget *parent  = 0);
	
	
protected:  
	
	void paintEvent(QPaintEvent* /*event*/);
	void keyPressEvent(QKeyEvent *event);

	
signals:
	void timeout();
	void collect(int);
	void die();
	
	
};
