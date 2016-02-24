//
// Created by Mark Jan Kamminga on 17-02-16.
//

#ifndef ROGUE_ITEMVISITABLE_H
#define ROGUE_ITEMVISITABLE_H

#include "Visitor.h"

class ItemVisitable {
public:
    virtual void accept(Visitor* visitor) = 0;
};

#endif //ROGUE_ITEMVISITABLE_H
