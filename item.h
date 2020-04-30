#ifndef _ITEM_H_
#define _ITEM_H_
#include <string>

class Item {
  protected:
   int x;
   int y;
   std::string itemType;
   char notation;
  public:
   Item(int x, int y, std::string itemType, char notation);
   virtual ~Item() = 0;
   int get_x();
   void set_x(int x);
   int get_y();
   void set_y(int y);
   virtual std::string get_Itemtype();
   virtual char get_Notation();
};

#endif




