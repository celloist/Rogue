//
// Created by Mark Jan Kamminga on 16-05-16.
//

#ifndef ROGUE_ITEMVISITOR_H_H
#define ROGUE_ITEMVISITOR_H_H

#include "Items/Weapon.h"
#include "Items/potion.h"
#include "Items/Armor.h"

using namespace std;

class BaseItemVisitor {
protected:
    string output;
    string type;
public:
    virtual void visit (Armor*) = 0;
    virtual void visit (Potion*) = 0;
    virtual void visit (Weapon* ) = 0;

    string getOutput () {
        return output;
    }

    string getType () {
        return type;
    }

};

#endif //ROGUE_ITEMVISITOR_H_H
