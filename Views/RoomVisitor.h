//
// Created by Mark Jan Kamminga on 14-05-16.
//

#ifndef ROGUE_ROOMVISITOR_H
#define ROGUE_ROOMVISITOR_H


#include "../Room.h"
#include "../Visitor.h"

class RoomVisitor : public Visitor {
public:
    virtual void visit(Room*);
    virtual void visit(ExitRoom*);
    string getOutput();
private:
    string output;
};


#endif //ROGUE_ROOMVISITOR_H
