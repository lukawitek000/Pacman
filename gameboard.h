#pragma once 


//PACMAN BOARD
#include <QWidget>
#include <QGridLayout>
#include <QImage>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>

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
	QVector<Wall*> walls;
	QVector<Snack*> snacks;
	QVector<SuperSnack*> superSnacks;   
	Gate *gate;
	int w;
	int h;
	int timerCount; 
	QTimer *timer;
	int speed = 10;
	
	LCDScore * score;  
	LCDScore * lives;
	 
private slots:
	void movePacman(); 
	  
	  
	 
	
public: 
	int boardTable[30][30];
	
	GameBoard(QWidget *parent  = 0);/*: QWidget(parent){ ss
		
		this-> resize(900, 900);
		int w = width() / 30;
		int h = height() / 30;
		
		for(int i=0; i<30; i++){
			for(int j=0; j<30; j++){
				boardTable[i][j] = 0;
			}
		}
		
		
		
		player = new Player(w, h);
		QImage board = QImage(QString("%1/prototypPlanszy.png").arg(QCoreApplication::applicationDirPath()));
		
		
	//	player->paint();
		//update();
		
		
		
		
		
		
	//	QColor color;
		QGridLayout *gridLayout = new QGridLayout;
		//gridLayout->setVerticalSpacing( 10);
		for(int x = 0; x<board.width(); x++){
			for(int y = 0; y<board.height(); y++){
				if(board.pixel(x, y) == qRgb(0,0,255)){
					gridLayout->addWidget(player, y, x);
					std::cout << "player add " << std::endl;
				}else if(board.pixel(x, y) == qRgb(0,0,0)){
					boardTable[x][y] = 1;
					Wall * wall = new Wall(x*w, y*h, w, h);
					walls.push_back(wall);
					gridLayout -> addWidget(walls[walls.size()-1], y, x);
					//std::cout << "wall add " << std::endl;
				}//else{
			}
		}
		
		std::cout << "horizontal spacing" << gridLayout->horizontalSpacing() <<std::endl;
		std::cout << "vertical spacing" << gridLayout->verticalSpacing() <<std::endl;
		
		setLayout(gridLayout);
		player->setFocus();
		//this->setStyleSheet("background-color:black;");
	};
	
	static int getBoardTableValueAt(int x, int y){
		return boardTable[x][y];
	};*/
protected:  
	
	void paintEvent(QPaintEvent* /*event*/);
	void keyPressEvent(QKeyEvent *event);

	
signals:
	void timeout();
	void collect(int);
};
