//
// Created by Mark Jan Kamminga on 17-05-16.
//

#ifndef ROGUE_BASEITEMVISITOR_H
#define ROGUE_BASEITEMVISITOR_H
class Armor;
class Potion;
class Weapon;
class Trap;

#include <string>

class BaseItemVisitor  {
protected:
    std::string output;
    std::string type;
public:
    virtual void visit (Armor*) = 0;
    virtual void visit (Potion*) = 0;
    virtual void visit (Weapon* ) = 0;
    virtual void visit (Trap* ) = 0;

    std::string getOutput() {
        return output;
    }

    std::string getType () {
        return type;
    }
};
#endif //ROGUE_BASEITEMVISITOR_H
