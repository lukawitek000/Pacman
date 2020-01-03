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
		
		Figure::mode = SCATTER;
		
		
		ghostTimer = 0;
		timerCount = 0;
		timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(movePacman()));
		
		score = new LCDScore(0, "SCORE");
		lives = new LCDScore(3, "LIVES");
		
		
		score->setFixedHeight(140);
		lives->setFixedHeight(140);
		
		
		dead = true;
		gameOver = false;
		win = false;
		
		connect(this, SIGNAL(collect(int)), score, SLOT(changeValue(int)));
		connect(this, SIGNAL(die()), lives, SLOT(takeLive()));
		
		board = QImage(QString("%1/Board.png").arg(QCoreApplication::applicationDirPath()));
		
		for(int i=0; i<30; i++){
			for(int j=0; j<30; j++){
				boardTable[i][j] = 0;
			}
		}
		gridLayout = new QGridLayout; 
		for(int x = 0; x<board.width(); x++){
			for(int y = 0; y<board.height(); y++){
				if(board.pixel(x, y) == qRgb(0,0,255)){
					player = new Player(x*w, y*h);
					gridLayout->addWidget(player, y, x);	
					playerInit = player->position;
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
				}
				else if(board.pixel(x, y) == qRgb(128, 128, 128)){
					//blokadka
					boardTable[x][y] = 10;
					gate = new Gate(x*w, y*h);
					walls.push_back(gate);
					gridLayout->addWidget(gate, y, x);
				}else if(board.pixel(x, y) == qRgb(127, 0, 0)){
					blinky = new Blinky(x*w, y*h);
					gridLayout -> addWidget(blinky, y, x);
					blinkyInit = blinky->position;
				}else if(board.pixel(x, y) == qRgb(0,255,255)){
					inky = new Inky(x*w, y*h);
					gridLayout -> addWidget(inky, y, x);
					inkyInit = inky->position;
				}else if(board.pixel(x,y) == qRgb(255, 106, 0)){
					clyde = new Clyde(x*w, y*h);
					gridLayout -> addWidget(clyde, y, x);
					clydeInit = clyde->position;
				}else if(board.pixel(x, y) == qRgb(255, 0, 220)){
					pinky = new Pinky(x*w, y*h);
					gridLayout -> addWidget(pinky, y, x);
					pinkyInit = pinky->position;
				}
			}
		}
		 
		layout = new QGridLayout;
		layout->addLayout(gridLayout, 0, 0);
		layout->addWidget(score, 1, 0);
		layout->addWidget(lives, 1, 1);
		
		QGridLayout *buttonLayout = new QGridLayout;
		
		QPushButton *quit = new QPushButton("quit");
		quit -> setFont(QFont("Times", 18, QFont::Bold));
		connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
		
		QPushButton *playAgain = new QPushButton("play again");
		playAgain -> setFont(QFont("Times", 18, QFont::Bold));
		connect(playAgain, SIGNAL(clicked()), this, SLOT(newGame()));
		
		
		buttonLayout->addWidget(quit, 0, 0);
		buttonLayout -> addWidget(playAgain, 1, 0);
		
		layout -> addLayout(buttonLayout, 1, 2);
		
		setLayout(layout);
		player->setFocus(); 
		
	
	} 
	
	
void GameBoard::init(){
	/*
	pinky->position = pinkyInit;
	blinky->position = blinkyInit;
	clyde->position = clydeInit;
	inky->position = inkyInit;
	
	player->position = playerInit;
	*/
	
	if(lives->getNum() == 0){
		gameOver = true;
	}
	/*
	pinky = new Pinky(pinkyInit.x(), pinkyInit.y());
	blinky = new Blinky(blinkyInit.x(), blinkyInit.y());
	inky = new Inky(inkyInit.x(), inkyInit.y());
	clyde = new Clyde(clydeInit.x(), clydeInit.y());
	
	//player = new Player(playerInit.x(), playerInit.y());
	player->position = playerInit;
	player->FigureRect.moveTo(player->position);
	player->dir = RIGHT;
	*/
	
	
	
	player->moveToInitPosition();
	blinky->moveToInitPosition();
	pinky->moveToInitPosition();
	inky->moveToInitPosition();
	clyde->moveToInitPosition();
	
	player->dir = RIGHT;
	Figure::mode = SCATTER;
	
	ghostTimer = 0;
	
	dead = true;
	
	timer->stop();
	
}
	
	
	

void GameBoard::movePacman(){
	//std::cout << "move Pacman " << std::endl;
	
	//gameOver = false;
	timerCount++; 
	ghostTimer++;    
	//std::cout << "ghostTimer = " << ghostTimer << std::endl;
	
	player->move(&timerCount, boardTable);
	
	if(!(Figure::mode == FRIGHTENED && ghostTimer%2==0)){
		blinky ->move(*player, boardTable, &ghostTimer);
		inky->move(*player, *blinky , boardTable, &ghostTimer);
		clyde ->move(*player, boardTable, &ghostTimer);
		pinky->move(*player, boardTable, &ghostTimer);
	}
	for(int i = 0; i < snacks.size(); i++){
		if(player->FigureRect.intersects(snacks[i]->snackRect)){
			if(snacks[i]->isSuperSnack){
				Figure::mode = FRIGHTENED;
				Figure::vulnerableCounter = 0;
				emit collect(10);
			}else{
				emit collect(1); 
			}
			snacks.remove(i);
			
			break; 
		}
	}
	
	if(snacks.isEmpty()){
		win = true;
		init();
	}
	
	if(player ->FigureRect.intersects(blinky->FigureRect) || player ->FigureRect.intersects(inky->FigureRect) || player ->FigureRect.intersects(clyde->FigureRect) || player ->FigureRect.intersects(pinky->FigureRect)){
		if(Figure::mode != FRIGHTENED){
			
			emit die();
			init();
			
			//QThread::msleep(1000);
		}else{
			emit collect(50);
			//srand(time(NULL));
			//int r = rand() % 50 + 300;
			//std::cout << "random x position = " << r << std::endl;
			if(player ->FigureRect.intersects(blinky->FigureRect)){
				//blinky = new Blinky(pinkyInit.x(), pinkyInit.y());
				blinky->position = inky->initPosition;
			}
			if(player ->FigureRect.intersects(inky->FigureRect)){
				//inky = new Inky(pinkyInit.x(), pinkyInit.y());
				//inky->position.setX(r);
				//inky->position.setY(300);
				inky->position = inky->initPosition;
			}
			if(player ->FigureRect.intersects(clyde->FigureRect)){
				//clyde = new Clyde(r, pinkyInit.y());
				clyde->position = inky->initPosition;
			}
			if(player ->FigureRect.intersects(pinky->FigureRect)){
				//pinky = new Pinky(r, pinkyInit.y());
				pinky->position = inky->initPosition;
			}
		}
	}
	update(); 
}
	
void GameBoard::paintEvent(QPaintEvent* /*event*/){ 
	
	//std::cout << "mode = " << Figure::mode << std::endl;
	
		QPainter painter(this);
			//std::cout << "draw here" << std::endl;
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
			//player->paintFigure(painter);
			QPen pen;
			//pen.setBrush(QBrush(Qt::SolidLine));
			pen.setColor(Qt::yellow);
			painter.setPen(pen);
			QFont font = painter.font();
			font.setPixelSize(30);
			font.setBold(true);
			font.setItalic(true);
			//font.setFamily("");
			painter.setFont(font);
			if(gameOver){
				painter.drawText(250, 385, "GAME OVER!");
			}else if (!win){
				painter.drawText(300, 385, "READY!");
				
			}
		}
		
		if(win){
			QPen pen;
			//pen.setBrush(QBrush(Qt::SolidLine));
			pen.setColor(Qt::yellow);
			painter.setPen(pen);
			QFont font = painter.font();
			font.setPixelSize(30);
			font.setBold(true);
			font.setItalic(true);
			//font.setFamily("");
			painter.setFont(font);
			painter.drawText(310, 385, "WIN!");
			//init();
		}
		
		
		
		//std::cout << "paint event "<< snacks.size() << std::endl;
};

 

void GameBoard::keyPressEvent(QKeyEvent *event){
	//std::cout << "keyerevent" << std::endl;
	dead = false;
	if(!(gameOver || win)){
		timer->start(speed);
	}
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




void GameBoard::newGame(){
	init();
	snacks.clear();
	for(int x = 0; x<board.width(); x++){
			for(int y = 0; y<board.height(); y++){
				if(board.pixel(x, y) == qRgb(255,0,0)){
					Snack *snack = new Snack(x*w, y*h);
					snacks.push_back(snack);
					//gridLayout->addWidget(snack, y, x);
					//boardTable[x][y] = 2; 
				}else if(board.pixel(x, y) == qRgb(0, 255, 0)){
					Snack * superSnack = new SuperSnack(x*w, y*h);
					snacks.push_back(superSnack);
					//gridLayout->addWidget(superSnack, y, x);
				}
			}
	}
	score->setNum(0);
	lives->setNum(3);
	gameOver = false;
	win = false;
	update();
	//std::cout << "after update()" << std::endl;
	player->setFocus();
}



