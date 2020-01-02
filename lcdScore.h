#pragma once
#include <QLCDNumber>
#include <QString>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>

class LCDScore : public QWidget{
	
	Q_OBJECT
	
private:
	QLCDNumber *lcd;
	QLabel *label;
	int num;
	
	
public:
	
	
	
	LCDScore(int score, const QString &name, QWidget * parent = 0) : QWidget(parent){
		num = score;
		lcd = new QLCDNumber(3);
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
	
	int getNum(){
		return num;
	};
	
	void setNum(int n){
		num = n;
		lcd->display(num);
		update();
	};
	
	
	
public slots:
	void changeValue(int value){
		num += value;
		lcd -> display(num);
	};
	
	void takeLive(){
		num--;
		lcd->display(num);
	};
	
};
