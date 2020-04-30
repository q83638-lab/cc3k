#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <cmath> //cmath or math? 
#include <string>
#include "player.h"
#include "item.h"
#include "gold.h" //??
#include "enemy.h"//??

using namespace std;

Player::Player(int hp, int atk, int def,int maxHP, int x, int y, string race, int id):
Character {hp, atk ,def,maxHP, x, y, race, '@'},gold{0},id{id},baseAtk{atk},baseDef{def},hasBarrier{false}{
    action = "Player character has spawned.";
}

int Player::getId(){
    return id;
}

void Player::setId(const int i)
{
    this->id = i;
}

std::string Player::getAction()
{
    return action;
}

int Player::getBaseAtk()
{
    return baseAtk;
}

int Player::getBaseDef()
{
    return baseDef;
}


int Player::getGold(){
    return gold;
}

//setGold and update Action
void Player::setGold(shared_ptr<Gold> g)
{  
    int amt = 0;
    if(g->isPickable()){
        if(get_race() == "Dwarf") {
            amt = g->getGold() * 2;
            gold += amt;
        }
        else if(get_race() == "Orc") {
            amt =  (int)ceil(g->getGold()/ 2.0);
            gold += amt;
        }
        else { 
            amt = g->getGold();
            gold += amt;
        }
    }
    ostringstream gold_str;
    gold_str << amt;

    action = "Based on your player type, you get: " + gold_str.str() + " gold. ";
   if(g->get_Itemtype() == "normal"){
        action += "PC gets a normal gold. Value:1 ";
    }
    else if(g->get_Itemtype()=="small"){
        action += "PC gets a small gold. Value:2 ";
    }
    else if(g->get_Itemtype()=="merchant hoard"){
        action += "PC gets a merchant hoard. Value:4 ";
    }
    else if(g->get_Itemtype()=="dragon hoard"){
        action += "PC gets a dragon hoard. Value:6 ";
    } 

}

void Player::setAction(const string s)
{
    this->action = s;
}


void Player::damage(shared_ptr<Enemy> e, vector<shared_ptr<Enemy>> enemies) {
    int combat = (int) ceil ((100.0 / (100+get_Def()))*e->get_Atk());

    ostringstream combat_str;
    combat_str << combat;
    int newdamage = e->get_HP() - combat;
    ostringstream hp_str;
    
    if(newdamage > 0){
        e->set_HP(newdamage);
        hp_str << newdamage; 
        action = "PC attacked " + e->get_race() + ", dealed "+ combat_str.str() + " damage. [" + e->get_race() + " HP:" + hp_str.str() + "]. ";
    } else { // the enemy is killled
        e->set_HP(0);
        action = "Dealed "+ combat_str.str() + " damage. " + e->get_race()+ " is killed. ";
        if(e->get_race()!="Merchant" && e->get_race()!="Dragon"){
            gold+=1;
        } else if(e->get_race() == "Dragon"){
            e->setDragonHoard(true);
        } else if(e->get_race() == "Merchant"){
            //drop gold in void Floor::pAttack(string dir)
        }
    }
    if (e->get_race() == "Merchant") {
        for (unsigned int i = 0; i < enemies.size(); i++) {
            if(enemies[i]->get_notation() == 'M')
            enemies[i]->setHostile(true);
        }
    }
}

//changes the direction of the PC 
void Player::move(string dir)
{
    if(dir == "no"){
        set_x(get_x()-1);
        action = "PC moves North. ";
    }
    else if(dir == "so"){
        set_x(get_x()+1);
        action = "PC moves South. ";
    }
    else if(dir == "we"){
        set_y(get_y()-1);
        action = "PC moves West. ";
    }
    else if(dir == "ea"){
        set_y(get_y()+1);
        action = "PC moves East. ";
    }    
    else if(dir == "ne"){
        set_x(get_x()-1);
        set_y(get_y()+1);
        action = "PC moves NorthEast. ";
    }
    else if(dir == "se"){
        set_x(get_x()+1);
        set_y(get_y()+1);
        action = "PC moves SouthEast. ";
    }
    else if(dir == "sw"){
        set_x(get_x()+1);
        set_y(get_y()-1);
        action = "PC moves SouthWest. ";
    }
    else if(dir == "nw"){
        set_x(get_x()-1);
        set_y(get_y()-1);
        action = "PC moves NorthWest. ";    
    }
}     

void Player::applyPotion(shared_ptr<Potion> pp){
    int effect = pp->getPotion();
    if(get_race() == "Elf"){
        if(effect < 0){
            effect = effect * -1;
        }
    }
    if(pp->get_Itemtype() == "RH"){
        if(get_HP()+effect < get_maxHP()){
            set_HP(get_HP()+effect);
            action = "PC uses Restore Health. ";
            return;
        }
        action = "PC cannot use Restore Health. ";
    } else if(pp->get_Itemtype() == "PH"){
        if(get_HP()+effect >= 0){
            set_HP(get_HP()+effect);
            action = "PC uses Poison Health. ";
            return;
        }
        action = "PC cannot use Poison Health. ";
    } else if(pp->get_Itemtype() == "BA"){
        set_Atk(get_Atk()+effect);
        action = "PC uses Boost Atk. ";
        return;
    } else if(pp->get_Itemtype() == "WA"){
        if(get_Atk()+effect >= 0){
            set_Atk(get_Atk()+effect);
            action = "PC uses Wound Atk. ";
            return;
        }
        action = "PC cannot use Wound Atk. ";
    } else if(pp->get_Itemtype() == "BD"){
        set_Def(get_Def()+effect);
        action = "PC uses Boost Def. ";
           return;
    } else if(pp->get_Itemtype() == "WD"){
        if(get_Def()+effect >= 0){
            set_Def(get_Def()+effect);
            action = "PC uses Wound Def. ";
            return;
        }
        action = "PC cannot use Wound Def. ";
    }
}

Player :: ~Player(){}

bool Player::getBarrier(){
    return hasBarrier;
}

void Player::setBarrier(bool b){
    hasBarrier = b;
    action = "You got the Barrier Suit! Your damage will be reduced by half. ";
}



//initializes the PC 
Human :: Human(int x,int y,int id):Player{140,20,20,140,x,y,"Human",id} {}

Dwarf :: Dwarf(int x,int y,int id):Player{100,20,30,100,x,y,"Dwarf",id} {}

Elf :: Elf(int x,int y,int id):Player{140,30,10,140,x,y,"Elf",id}{}

Orc :: Orc(int x,int y,int id):Player{180,30,25,180,x,y,"Orc",id}{}



