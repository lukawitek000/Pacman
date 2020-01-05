#include "gameboard.h"

#include <iostream>
#include <QPalette>
#include <QTimer>
#include <QPen>
#include <QThread>


#define POINT_FOR_NORMAL_SNACK 1
#define POINT_FOR_SUPER_SNACK 10
#define POINT_FOR_KILLING_GHOST 50

#define PLAYER  qRgb(0,0,255)
#define WALL qRgb(0,0,0)
#define SNACK qRgb(255,0,0)
#define SUPER_SNACK qRgb(0, 255, 0)
#define GATE qRgb(128, 128, 128)

#define BLINKY qRgb(127, 0, 0)
#define PINKY qRgb(255, 0, 220)
#define INKY qRgb(0,255,255)
#define CLYDE qRgb(255, 106, 0)

#define INITIAL_LIVES 3
#define INITIAL_SCORE 0

#define HOW_TIMES_LOWER_SPEED_OF_FRIGHTENED_GHOSTS 2

#define DELAY_AT_THE_BEGINNING_IN_MS 1000

QVector<Wall*> GameBoard::walls; 
const int GameBoard::sizeOfTile; 
const int GameBoard::heightOfLCD;



GameBoard::GameBoard(QWidget *parent): QWidget(parent){
	createBackground();
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	
	createLCDDisplays();
	createButtons();
	createLayout();
	init();
	setLayout(layout);
	player->setFocus(); 
	
	
} 


void GameBoard::createLayout(){
	layout = new QGridLayout;
	layout->addLayout(gridLayout, 0, 0);
	layout->addWidget(score, 1, 0);
	layout->addWidget(lives, 1, 1);
	layout -> addLayout(buttonLayout, 1, 2);
}


void GameBoard::createLCDDisplays(){
	score = new LCDScore(INITIAL_SCORE, "SCORE");
	lives = new LCDScore(INITIAL_LIVES, "LIVES");
	
	score->setFixedHeight(heightOfLCD);
	lives->setFixedHeight(heightOfLCD);
	
	connect(this, SIGNAL(collect(int)), score, SLOT(changeValue(int)));
	connect(this, SIGNAL(die()), lives, SLOT(takeLive()));
}


void GameBoard::createButtons(){
	buttonLayout = new QGridLayout;
	
	QPushButton *quit = new QPushButton("quit");
	quit -> setFont(QFont("Times", 18, QFont::Bold));
	connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
	
	QPushButton *playAgain = new QPushButton("play again");
	playAgain -> setFont(QFont("Times", 18, QFont::Bold));
	connect(playAgain, SIGNAL(clicked()), this, SLOT(newGame()));
	
	buttonLayout->addWidget(quit, 0, 0);
	buttonLayout -> addWidget(playAgain, 1, 0);
}


void GameBoard::createBackground(){
	board = QImage(QString("%1/Board.png").arg(QCoreApplication::applicationDirPath()));
	
	QPalette pal = this->palette();
	pal.setColor(QPalette::Window, Qt::black);
	this->setPalette(pal);
	this-> setFixedSize(board.width()*sizeOfTile, board.height()*sizeOfTile + heightOfLCD);
	readTheBoard();
}


void GameBoard::readTheBoard(){
	gridLayout = new QGridLayout; 
	for(int x = 0; x<board.width(); x++){
		for(int y = 0; y<board.height(); y++){
			if(board.pixel(x, y) == PLAYER){
				player = new Player(x*sizeOfTile, y*sizeOfTile);
				gridLayout->addWidget(player, y, x);	
			}else if(board.pixel(x, y) == WALL){
				Wall * wall = new Wall(x*sizeOfTile, y*sizeOfTile);
				walls.push_back(wall);
				gridLayout -> addWidget(wall, y, x);
			}else if(board.pixel(x, y) == SNACK){
				Snack *snack = new Snack(x*sizeOfTile, y*sizeOfTile);
				snacks.push_back(snack);
				gridLayout->addWidget(snack, y, x); 
			}else if(board.pixel(x, y) == SUPER_SNACK){
				Snack * superSnack = new SuperSnack(x*sizeOfTile, y*sizeOfTile);
				snacks.push_back(superSnack);
				gridLayout->addWidget(superSnack, y, x);
			}else if(board.pixel(x, y) == GATE){
				Gate *gate = new Gate(x*sizeOfTile, y*sizeOfTile);
				walls.push_back(gate);
				gridLayout->addWidget(gate, y, x);
			}else if(board.pixel(x, y) == BLINKY){
				blinky = new Blinky(x*sizeOfTile, y*sizeOfTile);
				gridLayout -> addWidget(blinky, y, x);
			}else if(board.pixel(x, y) == INKY){
				inky = new Inky(x*sizeOfTile, y*sizeOfTile);
				gridLayout -> addWidget(inky, y, x);
			}else if(board.pixel(x,y) == CLYDE){
				clyde = new Clyde(x*sizeOfTile, y*sizeOfTile);
				gridLayout -> addWidget(clyde, y, x);
			}else if(board.pixel(x, y) == PINKY){
				pinky = new Pinky(x*sizeOfTile, y*sizeOfTile);
				gridLayout -> addWidget(pinky, y, x);
			}
		}
	}
	
}



void GameBoard::init(){
	if(lives->getNum() == 0){
		gameOver = true;
	}else{
		gameOver = false;
	}
	player->moveToInitPosition();
	blinky->moveToInitPosition();
	pinky->moveToInitPosition();
	inky->moveToInitPosition();
	clyde->moveToInitPosition();
	
	Ghost::mode = SCATTER;
	Ghost::ghostTimer = 0;
	Player::playerTimer = 0;
	dead = true;
	win = false;
	timer->stop();
}


void GameBoard::paintEvent(QPaintEvent* /*event*/){ 
	QPainter painter(this);
	for(int i = 0; i<walls.size(); i++){
		walls[i]->paintWall(painter);
	}
	for(int i = 0; i<snacks.size(); i++){
		snacks[i]->paintSnack(painter);
	}
	player->paintFigure(painter);
	blinky->paintFigure(painter);
	inky->paintFigure(painter);  
	clyde->paintFigure(painter); 
	pinky->paintFigure(painter);
	if(dead){
		paintText(painter);
	}
}


void GameBoard::paintText(QPainter &painter){
	QPen pen;
	pen.setColor(Qt::yellow);
	painter.setPen(pen);
	QFont font = painter.font();
	font.setPixelSize(sizeOfTile);
	font.setBold(true);
	font.setItalic(true);
	painter.setFont(font);
	if(gameOver){
		painter.drawText(250, 385, "GAME OVER!");
	}else if(win){
		painter.drawText(310, 385, "WIN!");
	}
	else{
		painter.drawText(300, 385, "READY!");
	}
}


void GameBoard::keyPressEvent(QKeyEvent *event){
	if(dead){
		QThread::msleep(DELAY_AT_THE_BEGINNING_IN_MS);
	}
	dead = false;
	if(!(gameOver || win)){
		timer->start(speed);
	}
	getDirectionForPlayer(event);
}


void GameBoard::getDirectionForPlayer(QKeyEvent *event){
	if(event->key() == Qt::Key_Right){
		if(player->canMoveRight()){
			if(player->dir != RIGHT)
				Player::playerTimer = 0;
			player->dir = RIGHT;
		}
		player->nextDir = RIGHT;
	}else if(event->key() == Qt::Key_Left){
		if(player->canMoveLeft()){
			if(player->dir != LEFT)
				Player::playerTimer = 0;
			player->dir = LEFT;
		}
		player->nextDir = LEFT;
	}else if(event->key() == Qt::Key_Up){
		if(player->canMoveUp()){
			if(player->dir != UP)
				Player::playerTimer = 0;
			player->dir = UP;
		}
		player->nextDir = UP;
	}else if(event->key() == Qt::Key_Down){
		if(player->canMoveDown()){
			if(player->dir != DOWN)
				Player::playerTimer = 0;
			player->dir = DOWN;
		}
		player->nextDir = DOWN;
	}
}


void GameBoard::eatingSnacks(){
	for(int i = 0; i < snacks.size(); i++){
		if(player->FigureRect.intersects(snacks[i]->snackRect) && snacks[i]->isVisible){
			if(snacks[i]->isSuperSnack){
				Ghost::mode = FRIGHTENED;
				Ghost::vulnerableCounter = 0;
				emit collect(POINT_FOR_SUPER_SNACK);
			}else{
				emit collect(POINT_FOR_NORMAL_SNACK); 
			}
			snacks[i]->isVisible = false;
			break; 
		}
	}
}


void GameBoard::checkIfPlayerWon(){
	bool isEverySnackEaten = true;
	for(int i=0; i<snacks.size(); i++){
		if(snacks[i]->isVisible){
			isEverySnackEaten = false;
		}
	}
	if(isEverySnackEaten){
		win = true;
		dead = true;
		timer->stop();
	}
}


void GameBoard::checkContactPlayerWithGhost(){
	if(player ->FigureRect.intersects(blinky->FigureRect) || player ->FigureRect.intersects(inky->FigureRect) || player ->FigureRect.intersects(clyde->FigureRect) || player ->FigureRect.intersects(pinky->FigureRect)){
		if(Ghost::mode != FRIGHTENED){
			emit die();
			init();
		}else{
			emit collect(POINT_FOR_KILLING_GHOST);
			if(player ->FigureRect.intersects(blinky->FigureRect)){
				//blinky->position = inky->initPosition;
				blinky->moveCaughtGhostToHouse();
			}
			if(player ->FigureRect.intersects(inky->FigureRect)){
				//inky->position = inky->initPosition;
				inky->moveCaughtGhostToHouse();
			}
			if(player ->FigureRect.intersects(clyde->FigureRect)){
				//clyde->position = inky->initPosition;
				clyde->moveCaughtGhostToHouse();
			}
			if(player ->FigureRect.intersects(pinky->FigureRect)){
				//pinky->position = inky->initPosition;
				pinky->moveCaughtGhostToHouse();
			}
		}
	}
}


void GameBoard::movingOfFigures(){
	Player::playerTimer++; 
	Ghost::ghostTimer++;
	Ghost::selectMode();
	player->move();
	if(!(Ghost::mode == FRIGHTENED && Ghost::ghostTimer % HOW_TIMES_LOWER_SPEED_OF_FRIGHTENED_GHOSTS == 0)){
		blinky ->move(*player);
		inky->move(*player, *blinky);
		clyde ->move(*player);
		pinky->move(*player);
	}
}


int GameBoard::sizeOfWalls(){
	return walls.size();
}


Wall * GameBoard::getWall(int i){
	return walls[i];
}


/*-------------------SLOTS---------------------------------------*/


void GameBoard::move(){
	movingOfFigures();
	eatingSnacks();
	checkIfPlayerWon();
	checkContactPlayerWithGhost();
	update(); 
}


void GameBoard::newGame(){
	init();
	for(int i=0; i< snacks.size(); i++){
		snacks[i]->isVisible = true;
	}
	score->setNum(INITIAL_SCORE);
	lives->setNum(INITIAL_LIVES);
	update();
	player->setFocus();
}



