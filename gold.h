#ifndef GOLD_H_
#define GOLD_H_
#include "item.h"
#include <string>
class Gold : public Item
{
int gold;
bool ispickable;
public:
Gold(int x, int y, std::string item, char notation, int gold, bool ispickable);
~Gold();
void setGold(int gold);
int getGold();
bool isPickable();
void setIspickable(bool pickable);
};
#endif





