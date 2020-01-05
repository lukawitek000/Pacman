#pragma once
#include "snack.h"
#include <QWidget>
#include <QRect>
#include <QPainter>

class SuperSnack : public Snack{
private:
	const static int sizeOfSuperSnack = 10;
	
public:
	SuperSnack(int x, int y, QWidget* parent = 0);
};
