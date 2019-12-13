#include "gameboard.h"

#include <QPalette>

GameBoard::GameBoard(QWidget *parent): QWidget(parent){
		
		QPalette pal = this->palette();
		pal.setColor(QPalette::Window, Qt::black);
		this->setPalette(pal);
	
	
	
	
		this-> resize(900, 900);
		//this->setStyleSheet("background-color:black;");
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
				}else if(board.pixel(x, y) == qRgb(255,0,0)){
					Snack *snack = new Snack(x*w, y*h);
					snacks.push_back(snack);
					gridLayout->addWidget(snacks[snacks.size()-1], y, x);
				}
			}
		}
		
		std::cout << "horizontal spacing" << gridLayout->horizontalSpacing() <<std::endl;
		std::cout << "vertical spacing" << gridLayout->verticalSpacing() <<std::endl;
		
		setLayout(gridLayout);
		player->setFocus();
	
	}
	




void GameBoard::keyPressEvent(QKeyEvent *event){
		//std::cout << "keyerevent" << std::endl;
		player->move(event, boardTable);
//	player->move(event);
		update();
		
};
