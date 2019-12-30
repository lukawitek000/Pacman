#include "gameboard.h"
//#include "Player.h"

#include <iostream>

using namespace std;


bool Player::canMoveRight(int boardTable[30][30]){
	if(boardTable[(position.x() + playerRect.width())/30][position.y()/30] == 1 || boardTable[(position.x() + playerRect.width())/30][(position.y()+playerRect.height()-step)/30] == 1)
		return false;
	return true;
	
};


bool Player::canMoveLeft(int boardTable[30][30]){
	if(boardTable[(position.x()-step)/30][position.y()/30] == 1 || boardTable[(position.x()-step)/30][(position.y()+playerRect.height()-step)/30] == 1) //dlaczego tu musi być -5 czyli -step a w move right nie????
		return false;
	return true;
};



bool Player::canMoveUp(int boardTable[30][30]){
	if(boardTable[position.x()/30][(position.y()-step)/30] == 1 || boardTable[(position.x()+playerRect.width()-step)/30][(position.y()-step)/30])
		return false;
	return true;
};

bool Player::canMoveDown(int boardTable[30][30]){
	if(boardTable[position.x()/30][(position.y()+playerRect.height())/30] == 1 || boardTable[(position.x() + playerRect.width()-step)/30][(position.y()+playerRect.height())/30])
		return false;
	return true;
	
	
};
