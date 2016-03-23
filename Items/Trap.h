//
// Created by Mark Jan Kamminga on 28-02-16.
//

#ifndef ROGUE_TRAP_H
#define ROGUE_TRAP_H

#include "Item.h"

using namespace std;

class Trap : public Item  {
public:
    Trap(string name,itemType type,int value) : Item(name, type, value) {}
    virtual string use(Hero* hero);
};


#endif //ROGUE_TRAP_H
