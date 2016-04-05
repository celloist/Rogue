//
// Created by alhric on 02-Nov-15.
//

#ifndef ROGUE_ITEM_H
#define ROGUE_ITEM_H

#include "iostream"


class Hero;

using namespace std;

enum itemType{
    weapon,
    potion,
    armor,
    trap
};

using namespace std;

class Item {

public:
    Item(string name,itemType type,int value);
    ~Item();
    string getName();
    itemType getType();
    int getValue();
    virtual string use(Hero* hero);
    virtual bool isUsed();

protected:
    string name;
    itemType type;
    int value;
};

#endif //ROGUE_ITEM_H
