#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

class Character{
	int HP;
	int Atk;
	int Def;
	int maxHP;
	int pos_x; //character's position x
	int pos_y; //character's position y
	std::string race; //eg. "vampire"
	char notation; //eg. 'v', '@'
public:
	Character(int hp, int atk, int def, int max, int x, int y, std::string race, char notation);
	virtual ~Character() = 0;
	int get_HP();
	void set_HP(int h);
	int get_Atk();
	void set_Atk(int a);
	int get_Def();
	void set_Def(int d);
	int get_maxHP();
	void set_maxHP(int m);
	int get_x();
	void set_x(int x);
	int get_y();
	void set_y(int y);
	std::string get_race();
	char get_notation();
};

#endif


