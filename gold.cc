#include <string>
#include "gold.h"

Gold::Gold(int x, int y, std::string item, char notation, int gold, bool ispickable)
:Item{x,y,item,notation}, gold{gold},ispickable{ispickable} {}

void Gold::setGold(int gold)
{
	this->gold = gold; 
}

int Gold::getGold()
{
	return gold;
}

bool Gold::isPickable()
{
	return ispickable;
}

void Gold::setIspickable(bool pickable)
{
	ispickable = pickable;
}
Gold::~Gold(){};


