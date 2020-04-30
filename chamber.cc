#include "chamber.h"
#include <cstdlib> //rand
#include <memory> //shared ptr
#include <iostream>
#include <ctime>
using namespace std;
Chamber::Chamber(int id, vector<std::vector<char>>& display): display{display}{
	if(id == 0){ //top left
		chamberNum = 0;
		row = 4;
		col = 26;
		topLeft = {3,3};
	} else if(id == 3){ //bottom left
		chamberNum = 3;
		row = 7;
		col = 21;
		topLeft = {15,4};
	} else if(id == 1){//top right
		chamberNum = 1;
		row = 10;
		col = 37;
		topLeft = {3,39};
	} else if(id == 2){//middle
		chamberNum = 2;
		row = 3;
		col = 12;
		topLeft = {10,38};
	} else if (id == 4){//bottom right
		chamberNum = 4;
		row = 6;
		col = 39;
		topLeft = {16,37};
	}
}

Chamber::~Chamber(){}

int Chamber::getChamberNum(){
	return chamberNum;
}

int Chamber::getRow(){
	return row;
}

int Chamber::getCol(){
	return col;
}

int Chamber::checkTile(int x, int y){ //incomplete, come back after floor!
	return 0;
}

vector<int> Chamber::findRandom(){
	srand(time(NULL));
	while(true){
		int tempX = rand()%row;
		int tempY = rand()%col;
		if(display[tempX+topLeft[0]][tempY+topLeft[1]] == '.'){
			vector<int> pos;
			pos.emplace_back(tempX+topLeft[0]);
			pos.emplace_back(tempY+topLeft[1]);
			return pos;
		}
	}
}




