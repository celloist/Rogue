//
// Created by Mark Jan Kamminga on 16-05-16.
//

#ifndef ROGUE_ITEMVISITOR_H
#define ROGUE_ITEMVISITOR_H


#include "../BaseItemVisitor.h"

class ItemVisitor : public BaseItemVisitor {
public:
    virtual void visit (Armor*);
    virtual void visit (Potion*);
    virtual void visit (Weapon* );
};


#endif //ROGUE_ITEMVISITOR_H
