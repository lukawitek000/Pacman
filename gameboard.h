#pragma once 

//PACMAN BOARD
#include <QWidget>
#include <QGridLayout>
#include <QImage>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>

//class GameBoard;
#include "Player.h"
#include "Wall.h"
#include "snack.h"



class GameBoard : public QWidget{
	
	Q_OBJECT
	
private:
	Player *player;
	QVector<Wall*> walls;
	QVector<Snack*> snacks;
	int w;
	int h;
	int timerCount;
	QTimer *timer;
	int speed = 10;
	//int step = 1;
	
private slots:
	void movePacman();
	
	
	
	
public:
	int boardTable[30][30];
	
	GameBoard(QWidget *parent  = 0);/*: QWidget(parent){
		
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
	
	void paintEvent(QPaintEvent* /*event*/){
		QPainter painter(this);
		QRect background(0, 0, w*30, h*30);
		//painter.setPen(Qt::NoPen);
		//painter.setBrush(Qt::black);
		//painter.drawRect(background);
		painter.fillRect(background, Qt::black);
		player->paintPlayer(painter);
		for(int i = 0; i<walls.size(); i++){
			walls[i]->paintWall(painter);
		}
		for(int i = 0; i<snacks.size(); i++){
			snacks[i]->paintSnack(painter);
		}
	};
	
	void keyPressEvent(QKeyEvent *event);

	
signals:
	void timeout();
};
