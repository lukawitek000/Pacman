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
	LCDScore(int score, const QString &name, QWidget * parent = 0);
	int getNum();
	void setNum(int n);
public slots:
	void changeValue(int value);
	void takeLive();
};

