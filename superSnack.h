#pragma once


class SuperSnack : public Snack{
	
	
	
	
public:
	//QRect snackRect;
	SuperSnack(int x, int y, QWidget* parent = 0) : Snack(parent){
		snackRect = QRect(x+10, y+10, 10, 10);
		isSuperSnack = true;
		//std::cout << " creating superSnack" << std::endl;
	};
};
