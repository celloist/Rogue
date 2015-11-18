//
// Created by alhric on 02-Nov-15.
//

#ifndef ROGUE_ITEM_H
#define ROGUE_ITEM_H

#include "iostream"
#include "../Characters/Hero.h"

using namespace std;

enum itemType{
    weapon,
    potion,
    armor
};

using namespace std;

class Item {
public:
    Item(string name,itemType type,int value);
    string getName();
    itemType getType();
    int getValue();
    virtual void use(Hero* hero) = 0;

protected:
    string name;
    itemType type;
    int value;
};

#endif //ROGUE_ITEM_H
