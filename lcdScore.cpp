#include "lcdScore.h"

	LCDScore::LCDScore(int score, const QString &name, QWidget * parent) : QWidget(parent){
		num = score;
		lcd = new QLCDNumber(4);
		lcd->setSegmentStyle(QLCDNumber::Filled);
		//lcd -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
		lcd -> setMinimumHeight(100);
		lcd->display(score);
		lcd -> setStyleSheet("border: 0px; color: white");
		//lcd -> setStyleSheet("font-size: 50px");
		
		
		label = new QLabel;
		label -> setAlignment(Qt::AlignHCenter | Qt::AlignTop);
		//label -> setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		label ->setText(name);
		//label ->setStyleSheet("{color: #C0BBFE}");
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
	
