#include "lcdScore.h"

#define NUMBER_OF_DIGITS 4
#define MINIMUM_HEIGHT_OF_LCD 100

LCDScore::LCDScore(int score, const QString &name, QWidget * parent) : QWidget(parent){
	num = score;
	lcd = new QLCDNumber(NUMBER_OF_DIGITS);
	lcd -> setSegmentStyle(QLCDNumber::Filled);
	lcd -> setMinimumHeight(MINIMUM_HEIGHT_OF_LCD);
	lcd -> display(score);
	lcd -> setStyleSheet("border: 0px; color: white");
	label = new QLabel;
	label -> setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	label -> setText(name);
	label -> setStyleSheet("color : #FF00FF");
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(lcd);
	layout->addWidget(label);
	setLayout(layout);
};


int LCDScore::getNum(){
	return num;
};


void LCDScore::setNum(int n){
	num = n;
	lcd->display(num);
	update();
};


/*----------------SLOTS-----------------------------------------*/	


void LCDScore::changeValue(int value){
	num += value;
	lcd -> display(num);
};


void LCDScore::takeLive(){
	num--;
	lcd->display(num);
};

