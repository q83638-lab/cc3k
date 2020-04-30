#ifndef PLAYER_H
#define PLAYER_H
#include "character.h" 
#include "gold.h"
#include "potion.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Enemy;
class Player: public Character
{   
    int gold;
    int id; 
    int baseAtk,baseDef;
    std::string action;
    bool hasBarrier;
  public:
    Player(int hp, int atk, int def,int maxHP, int x, int y, std::string race, int id);

    int getId();
    void setId(const int i);

    std::string getAction();

    int getBaseAtk();
    int getBaseDef(); 

    int getGold();
    void setGold(std::shared_ptr<Gold> g);   
    
    void setAction(const std::string s);
   
    
    void damage(std::shared_ptr<Enemy> e, std::vector<std::shared_ptr<Enemy>> enemies);

    void move(std::string dir);      

    void applyPotion(std::shared_ptr<Potion> pp);

    bool getBarrier();
    void setBarrier(bool b);


    virtual ~Player();

};


class Human : public Player{  
    public:
        Human(int x=-1, int y=-1, int id=-1);
};

class Dwarf : public Player
{
    public:
        Dwarf(int x=-1, int y=-1, int id=-1);
};

class Elf : public Player
{
    public:
        Elf(int x=-1, int y=-1, int id=-1);
};

class Orc : public Player
{
    public:
        Orc(int x=-1,int y=-1, int id=-1);
        
};
#endif



