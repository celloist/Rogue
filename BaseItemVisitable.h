//
// Created by Mark Jan Kamminga on 16-05-16.
//

#ifndef ROGUE_BASEITEMVISITABLE_H
#define ROGUE_BASEITEMVISITABLE_H

#include "BaseItemVisitor.h"

class BaseItemVisitable {
public:
    virtual void accept(BaseItemVisitor* visitor) = 0;
};
#endif //ROGUE_BASEITEMVISITABLE_H
