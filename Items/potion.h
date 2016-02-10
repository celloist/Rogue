//
// Created by alhric on 12-Nov-15.
//

#ifndef ROGUE_POTION_H
#define ROGUE_POTION_H
#include "Item.h"

class Potion : public Item{

public:
    Potion(string name,itemType type,int value) : Item(name, type, value) {}
    string use(Hero* hero);
    bool isUsed();

private:
    bool used;
};
#endif //ROGUE_POTION_H
