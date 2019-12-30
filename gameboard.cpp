#include "gameboard.h"

#include <QPalette>
#include <QTimer>
#include <QPen>

GameBoard::GameBoard(QWidget *parent): QWidget(parent){
		
	
		QPalette pal = this->palette();
		pal.setColor(QPalette::Window, Qt::black);
		this->setPalette(pal);
	
	
	
	
		this-> setFixedSize(690, 800);
		w = 30;
		h = 30;
		
		
		
		
		
		
		

		timerCount = 0;
		timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(movePacman()));
		
		score = new LCDScore(0, "SCORE");
		lives = new LCDScore(3, "LIVES");
		
		
		score->setFixedHeight(140);
		lives->setFixedHeight(140);
		
		
		
		
		
		
		connect(this, SIGNAL(collect(int)), score, SLOT(changeValue(int)));
		
		
		QImage board = QImage(QString("%1/prototypPlanszy.png").arg(QCoreApplication::applicationDirPath()));
		
		for(int i=0; i<30; i++){
			for(int j=0; j<30; j++){
				boardTable[i][j] = 0;
			}
		}
		QGridLayout *gridLayout = new QGridLayout;
		//gridLayout->setVerticalSpacing( 10);
		for(int x = 0; x<board.width(); x++){
			for(int y = 0; y<board.height(); y++){
				if(board.pixel(x, y) == qRgb(0,0,255)){
					player = new Player(x*w, y*h);
					gridLayout->addWidget(player, y, x);	
					std::cout << "player add " << std::endl;
				}else if(board.pixel(x, y) == qRgb(0,0,0)){
					boardTable[x][y] = 1;
					Wall * wall = new Wall(x*w, y*h, w, h);
					walls.push_back(wall);
					gridLayout -> addWidget(wall, y, x);
					//std::cout << "wall add " << std::endl;
				}else if(board.pixel(x, y) == qRgb(255,0,0)){
					Snack *snack = new Snack(x*w, y*h);
					snacks.push_back(snack);
					gridLayout->addWidget(snack, y, x);
					//boardTable[x][y] = 2; 
				}else if(board.pixel(x, y) == qRgb(0, 255, 0)){
					Snack * superSnack = new SuperSnack(x*w, y*h);
					snacks.push_back(superSnack);
					gridLayout->addWidget(superSnack, y, x);
				}else if(board.pixel(x, y) == qRgb(128, 128, 128)){
					//blokadka
					boardTable[x][y] = 10;
					gate = new Gate(x*w, y*h);
					walls.push_back(gate);
					gridLayout->addWidget(gate, y, x);
					
					
				}else if(board.pixel(x, y) == qRgb(127, 0, 0)){
					blinky = new Blinky(x*w, y*h);
					gridLayout -> addWidget(blinky, y, x);
					
					
				}
			}
		}
		
		QGridLayout * layout = new QGridLayout;
		layout->addLayout(gridLayout, 0, 0);
		layout->addWidget(score, 1, 0);
		layout->addWidget(lives, 1, 1);
		
		
		
		std::cout << "horizontal spacing" << gridLayout->horizontalSpacing() <<std::endl;
		std::cout << "vertical spacing" << gridLayout->verticalSpacing() <<std::endl;
		
		std::cout << "board.width()" << board.width() <<std::endl;
		std::cout << "board.height()" << board.height() <<std::endl;
		
		setLayout(layout);
		player->setFocus();
		
		/*
		std::cout << "boardTable:" << std::endl;
		for(int i=0; i<30; i++){
			for(int j=0; j<30; j++){
				std::cout << boardTable[i][j] << " ";
			}
			std::cout << "\n";
		}*/
	
	}
	

void GameBoard::movePacman(){
	timerCount++;
	player->move(&timerCount, boardTable);
	for(int i = 0; i < snacks.size(); i++){
		if(player->FigureRect.intersects(snacks[i]->snackRect)){
			if(snacks[i]->isSuperSnack){
				emit collect(10);
			}else{
				emit collect(1);
			}
			snacks.remove(i);
			break;
		}
	}
	update();
}
	
void GameBoard::paintEvent(QPaintEvent* /*event*/){
		QPainter painter(this);
		player->paintFigure(painter);
		blinky->paintFigure(painter);
		for(int i = 0; i<walls.size(); i++){
			walls[i]->paintWall(painter);
		}
		for(int i = 0; i<snacks.size(); i++){
			snacks[i]->paintSnack(painter);
		}
		
		//std::cout << "num of snacks "<< snacks.size() << std::endl;
};

 

void GameBoard::keyPressEvent(QKeyEvent *event){
	//std::cout << "keyerevent" << std::endl;
	timer->start(speed);
	//timerCount = 0;
	if(event->key() == Qt::Key_Right){
		if(player->canMoveRight(boardTable)){
			if(player->dir != RIGHT)
				timerCount = 0;
			player->dir = RIGHT;
		}
		player->nextDir = RIGHT;
	}else if(event->key() == Qt::Key_Left){
		if(player->canMoveLeft(boardTable)){
			if(player->dir != LEFT)
				timerCount = 0;
			player->dir = LEFT;
		}
		player->nextDir = LEFT;
	}else if(event->key() == Qt::Key_Up){
		if(player->canMoveUp(boardTable)){
			if(player->dir != UP)
				timerCount = 0;
			player->dir = UP;
		}
		player->nextDir = UP;
	}else if(event->key() == Qt::Key_Down){
		if(player->canMoveDown(boardTable)){
			if(player->dir != DOWN)
				timerCount = 0;
			player->dir = DOWN;
		}
		player->nextDir = DOWN;
	}
	//movePacman(event);
//	player->move(event);
	//update();
		
};
