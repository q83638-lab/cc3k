#include "character.h"

using namespace std;

Character::Character(int hp, int atk, int def, int max, int x, int y, string race, char notation):
HP{hp}, Atk{atk}, Def{def}, maxHP{max}, pos_x{x}, pos_y{y}, race{race}, notation{notation} {}

Character::~Character(){}

int Character::get_HP(){
	return HP;
}

void Character::set_HP(int h){
	HP = h;
}

int Character::get_Atk(){
	return Atk;
}

void Character::set_Atk(int a){
	Atk = a;
}

int Character::get_Def(){
	return Def;
}

void Character::set_Def(int d){
	Def = d;
}

int Character::get_maxHP(){
	return maxHP;
}

void Character::set_maxHP(int m){
	maxHP = m;
}

int Character::get_x(){
	return pos_x;
}

void Character::set_x(int x){
	pos_x = x;
}

int Character::get_y(){
	return pos_y;
}

void Character::set_y(int y){
	pos_y = y;
}

string Character::get_race(){
	return race;
}

char Character::get_notation(){
	return notation;
}




