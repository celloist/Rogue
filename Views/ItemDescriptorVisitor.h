//
// Created by Mark Jan Kamminga on 17-05-16.
//

#ifndef ROGUE_ITEMDESCRIPTORVISITOR_H
#define ROGUE_ITEMDESCRIPTORVISITOR_H

#include "../BaseItemVisitor.h"

class ItemDescriptorVisitor : public BaseItemVisitor {
public:
    virtual void visit (Armor*);
    virtual void visit (Potion*);
    virtual void visit (Weapon* );
    virtual void visit (Trap*);
};

#endif //ROGUE_ITEMDESCRIPTORVISITOR_H
