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
#include <QMap>
#include <QString>


#include "Wall.h" 
#include "Gate.h"
#include "Figure.h"
#include "ghost.h"

#include "Player.h"

#include "snack.h"
#include "superSnack.h" 
#include "lcdScore.h"


#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h" 
#include "Pinky.h"


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
	void init();
	void paintEvent(QPaintEvent* /*event*/);
	void keyPressEvent(QKeyEvent *event);
	/*
	Blinky *blinky;
	Inky *inky;
	Clyde *clyde;
	Pinky *pinky;
	*/
	Player *player;
	
	QMap<QString, Ghost*> ghosts;
	
	QVector<Snack*> snacks;
	static QVector<Wall*> walls; 
	bool gameOver;
	bool win;
	bool dead;
	QTimer *timer;
	LCDScore * score;  
	LCDScore * lives;
	QImage board;
	QGridLayout *gridLayout;
	QGridLayout *layout;
	QGridLayout *buttonLayout;
 
	
public: 
	const static int sizeOfTile = 30; 
	const static int heightOfLCD = 140;
	const static int speed = 9;
	GameBoard(QWidget *parent  = 0);
	
	static int sizeOfWalls();
	static Wall * getWall(int i);
	/*
	~GameBoard(){
		//delete timer;
		delete player;
		delete score;
		delete lives;
		//delete gridLayout;
		//delete layout;
		//delete buttonLayout;
		
		for(int i=0; i<walls.size(); i++){
			delete walls[i];
		}
		for(int i= 0; i<snacks.size(); i++){
			delete snacks[i];
		}
		for(QMap<QString, Ghost*>::const_iterator it = ghosts.cbegin(), end = ghosts.cend(); it != end; ++it){
			delete it.value();
		}
		
		
	};
*/
private slots:
	void move(); 
	void newGame();  

signals:
	void timeout();
	void collect(int);
	void die();
};

