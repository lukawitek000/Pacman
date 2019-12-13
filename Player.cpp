#include "gameboard.h"
//#include "Player.h"

#include <iostream>

using namespace std;


bool Player::canMoveRight(int boardTable[30][30]){
	//std::cout << "canMoveRight" << Gameboard::getBoardTableValueAt(position.x()+step, position.y())  << std::endl;
	/*
	for(int i=0; i<30; i++){
			for(int j=0; j<30; j++){
				cout << boardTable[i][j] << endl;
			}
		}
		
	*/
	
	
	//std::cout << "canMoveRight" << boardTable[(position.x()+step + playerRect.width())/30][position.y()/30]  << std::endl;
	if(boardTable[(position.x() + playerRect.width())/30][position.y()/30] == 1 || boardTable[(position.x() + playerRect.width())/30][(position.y()+playerRect.height() -5)/30] == 1)
		return false;
	return true;
		
};


bool Player::canMoveLeft(int boardTable[30][30]){
	if(boardTable[(position.x()-5)/30][position.y()/30] == 1 || boardTable[(position.x()-5)/30][(position.y()+playerRect.height()-5)/30] == 1) //dlaczego tu musi być -5 czyli -step a w move right nie????
		return false;
	return true;
};



bool Player::canMoveUp(int boardTable[30][30]){
	if(boardTable[position.x()/30][(position.y()-5)/30] == 1 || boardTable[(position.x()+playerRect.width()-5)/30][(position.y()-5)/30])
		return false;
	return true;
};

bool Player::canMoveDown(int boardTable[30][30]){
	if(boardTable[position.x()/30][(position.y()+playerRect.height())/30] == 1 || boardTable[(position.x() + playerRect.width()-5)/30][(position.y()+playerRect.height())/30])
		return false;
	return true;
	
	
};
