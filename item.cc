#include <string>
#include <iostream>
#include "item.h"
using namespace std;

Item::Item(int x, int y, std::string itemType, char notation):
  x{x}, y{y}, itemType{itemType}, notation{notation} {}
Item::~Item() {}
int Item::get_x()
{
	return x;
}
void Item::set_x(int x)
{
	this->x = x;
}
int Item::get_y()
{
	return y;
}
void Item::set_y(int y)
{
	this->y = y;
}
std::string Item::get_Itemtype()
{
	return itemType;
}
char Item::get_Notation()
{
	return notation;
}


