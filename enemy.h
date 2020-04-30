#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "gold.h"
#include <string>
#include <memory>


class Player;

class Enemy: public Character{
	int gold;
	bool isHostile;
	bool hasCompass;
public:
	Enemy(int hp, int atk, int def, int max, int x, int y, std::string race, char notation, int gold, bool hostile, bool compass);
	~Enemy();
	int getGold();
	void setGold(int g);
	bool getHostile();
	void setHostile(bool hostile);
	bool getCompass();
	void setCompass(bool compass);

	void attack(std::shared_ptr<Player> pc);
	void move(std::string dir);

	virtual std::shared_ptr<Gold> getDragonHoard();
	virtual void setDragonHoard(bool pickable);
};

class Vampire: public Enemy{
public:
	Vampire(int x, int y): Enemy{50,25,25,50,x,y,"Vampire",'V',0,true,false}{}
	~Vampire(){}
};

class Werewolf: public Enemy{
public:
	Werewolf(int x, int y): Enemy{120,30,5,120,x,y,"Werewolf",'W',0,true,false}{}
	~Werewolf(){}
}; 

class Troll: public Enemy{
public:
	Troll(int x, int y): Enemy{120,25,15,129,x,y,"Troll",'T',0,true,false}{}
	~Troll(){}
};

class Goblin: public Enemy{
public:
	Goblin(int x, int y): Enemy{70,5,10,70,x,y,"Goblin",'N',0,true,false}{}
	~Goblin(){}
};

class Merchant: public Enemy{
public:
	Merchant(int x, int y): Enemy{30,70,5,30,x,y,"Merchant",'M',0,false,false}{}
	~Merchant(){}
};

class Dragon: public Enemy{ //add methods later
	std::shared_ptr<Gold> dragonHoard;
public:
	Dragon(int x, int y, std::shared_ptr<Gold> dragonHoard)
	: Enemy{150,20,20,150,x,y,"Dragon",'D',0,false,false}, dragonHoard{dragonHoard}{}
	~Dragon(){}
	std::shared_ptr<Gold> getDragonHoard() override;
	void setDragonHoard(bool pickable) override;
};

class Phoenix: public Enemy{
public:
	Phoenix(int x, int y): Enemy{50,35,20,50,x,y,"Phoenix",'X',0,true,false}{}
	~Phoenix(){}
};

#endif


