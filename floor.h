#ifndef FLOOR_H
#define FLOOR_H
#include <string>
#include <vector>
#include <memory>
#include "player.h"
#include "enemy.h"
#include "chamber.h"
#include "gold.h"
#include "potion.h"


class Floor{
	int level, barrierLevel;
	std::shared_ptr<Player> player;
	std::vector<std::vector<char>> display;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Chamber>> chambers;
	std::vector<std::shared_ptr<Potion>> potions;
	std::vector<std::shared_ptr<Gold>> golds;
	char origSymbol;
	bool hasWon;
public:
	Floor(int level, std::string file = "default.txt");
	void printFloor();//add display msg
	void genGold();
	void genPlayer();
	void genStair();
	void genPotion();
	void genChamber();
	void genEnemy();
	std::vector<int> checkTile(std::string dir);//returns position after moving player to dir
	bool movePlayer(std::string dir);
	bool withinBlock(int ex, int ey);
	void moveToNeighbour(std::shared_ptr<Enemy> pe);
	void moveEnemy();
	bool usePotion(std::string dir);
	int getLevel();
	void setLevel(int level);
	void sethasWon(bool won);
	bool hasLost();
	int getGold();
	void setAction(std::string action);
	bool checkDisplay (int x, int y, char c);
	void generateandprint();
	void reset();
	void newLevel();
	int enemyIndex();
	void readfile(std::string file);
	void pAttack(std::string dir);
	int enemyIndex(int x, int y );
	void setPlayer (std:: shared_ptr<Player> pp);
	void readFloor(std::string file);
	~Floor();

	//void createFloor();
};


#endif

