#include "enemy.h"
#include "player.h"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <memory>
using namespace std;

Enemy::Enemy(int hp, int atk, int def, int max, int x, int y, string race, char notation, int gold, bool hostile, bool compass):
Character{hp, atk, def, max, x, y, race, notation}, gold{gold}, isHostile{hostile}, hasCompass{compass} {}

Enemy::~Enemy(){}

int Enemy::getGold(){
	return gold;
}

void Enemy::setGold(int g){
	gold = g;
}

bool Enemy::getHostile(){
	return isHostile;
}

void Enemy::setHostile(bool hostile){
	isHostile = hostile;
}

bool Enemy::getCompass(){
	return hasCompass;
}
void Enemy::setCompass(bool compass){
	hasCompass = compass;
}

void Enemy::attack(shared_ptr<Player> pc){ //this enemy attacks player pc
	if(isHostile){
		int random = rand()%2;
		if(random){
			int damage = ceil((100.0/(100+pc->get_Def()))*get_Atk());
			if(pc->getBarrier()){
				damage = ceil(damage/2);
			}
			int curHP = pc->get_HP();
			if(curHP - damage > 0){
				pc->set_HP(curHP-damage);
				ostringstream combat_str;
    			combat_str << damage;
				pc->setAction(pc->getAction()+get_notation()+" deals "+combat_str.str()+" damage to PC. ");
			} else{//player dies
				pc->set_HP(0);
			}
		} else{
			pc->setAction(pc->getAction()+get_notation()+" missed the target.");
		}
	}
}

void Enemy::move(string dir){
	if(dir == "no"){
		set_x(get_x()-1);
	} else if(dir == "ne"){
		set_x(get_x()-1);
        set_y(get_y()+1);
	} else if(dir == "ea"){
		set_y(get_y()+1);
	} else if(dir == "se"){
		set_x(get_x()+1);
        set_y(get_y()+1);
	} else if(dir == "so"){
		set_x(get_x()+1);
	} else if(dir == "sw"){
		set_x(get_x()+1);
        set_y(get_y()-1);
	} else if(dir == "we"){
		set_y(get_y()-1);
	} else if(dir == "nw"){
		set_x(get_x()-1);
        set_y(get_y()-1);
	}
}

shared_ptr<Gold> Enemy::getDragonHoard(){}

void Enemy::setDragonHoard(bool pickable){}

shared_ptr<Gold> Dragon::getDragonHoard(){
	return dragonHoard;
}

void Dragon::setDragonHoard(bool pickable){
	dragonHoard->setIspickable(pickable);
}


