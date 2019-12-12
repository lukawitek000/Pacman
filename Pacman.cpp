
#include <iostream> 
//#include <Qt>
#include <QFont>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QPen>
#include <QtGui>
#include <QScrollArea>
#include <QObject>
#include <QLCDNumber>
#include <QSlider>
#include <QVBoxLayout>

#include "gameboard.h"

//using namespace std; 


int main(int argc, char* argv[]) 
{
	
	
	QApplication app(argc, argv);
	GameBoard gameboard;
	//gameboard.resize(900, 900);
	gameboard.show();
	
	
	

	return app.exec();

}
