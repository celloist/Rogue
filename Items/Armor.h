//
// Created by alhric on 12-Nov-15.
//

#ifndef ROGUE_ARMOR_H
#define ROGUE_ARMOR_H


#include "Item.h"

class Armor : public Item{

public:
    Armor(string name,itemType type,int value) : Item(name, type, value) {}
    string use(Hero* hero);
    virtual string getDescription();
};
#endif //ROGUE_ARMOR_H
