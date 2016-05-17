//
// Created by alhric on 12-Nov-15.
//

#ifndef ROGUE_WEAPON_H
#define ROGUE_WEAPON_H
#include "Item.h"

using namespace std;

class Weapon : public Item{

public:
    Weapon(string name,itemType type,int value) : Item(name, type, value) {}
    string use(Hero* hero);
    virtual string getDescription();
    virtual void accept(BaseItemVisitor*);
};
#endif //ROGUE_WEAPON_H
