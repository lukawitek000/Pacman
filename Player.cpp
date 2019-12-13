#include "gameboard.h"
//#include "Player.h"

#include <iostream>

using namespace std;


bool Player::canMoveRight(int step){
	//std::cout << "canMoveRight" << Gameboard::getBoardTableValueAt(position.x()+step, position.y())  << std::endl;
	std::cout << "canMoveRight" << Gameboard::boardTable[position.x()+step][position.y()]  << std::endl;
	//if(Gameboard::getBoardTableValueAt(position.x()+step, position.y()) == 1)
	//	return false;
	return true;
		
};
