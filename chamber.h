#ifndef CHAMBER_H
#define CHAMBER_H
#include <string>
#include <vector>

class Chamber{
	std::vector<std::vector<char>>& display; //2D array of char to store text display
	int chamberNum;
	int row;
	int col;
	std::vector<int> topLeft;
public:
	Chamber(int id, std::vector<std::vector<char>>& display);
	~Chamber();
	int getChamberNum();
	int getRow();
	int getCol();

	int checkTile(int x, int y);//incomplete
	std::vector<int> findRandom();
};

#endif

