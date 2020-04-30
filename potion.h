#ifndef POTION_H_
#define POTION_H_
#include "item.h"

class Potion: public Item {
  int potion;
  public:
   Potion(int x, int y, std::string item, char notation, int value);
    ~Potion();
   int getPotion();
};

#endif




