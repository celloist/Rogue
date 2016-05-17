//
// Created by alhric on 02-Nov-15.
//

#ifndef ROGUE_ITEM_H
#define ROGUE_ITEM_H

#include "iostream"
#include "../BaseItemVisitable.h"


class Hero;

using namespace std;

enum itemType{
    weapon,
    potion,
    armor,
    trap
};

using namespace std;

class Item, public BaseItemVisitable {

public:
    Item(string name,itemType type,int value);
    ~Item();
    string getName();
    itemType getType();
    virtual string getDescription() = 0;
    int getValue();
    virtual string use(Hero* hero);
    virtual bool isUsed();
    virtual void accept(BaseItemVisitor*);

protected:
    string name;
    itemType type;
    int value;
};

#endif //ROGUE_ITEM_H
