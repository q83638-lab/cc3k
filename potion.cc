#include <string>
#include "potion.h"

using namespace std;

Potion::Potion(int x, int y, string item, char notation, int potion):
  Item{x, y, item, notation}, potion{potion} {}

int Potion::getPotion()
{
	return potion;
}

Potion::~Potion() {}





