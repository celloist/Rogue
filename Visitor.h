//
// Created by Mark Jan Kamminga on 14-02-16.
//

#ifndef ROGUE_VISITOR_H
#define ROGUE_VISITOR_H

class Room;
class ExitRoom;

class Visitor {
public:
    virtual void visit(Room*) = 0;
    virtual void visit(ExitRoom*) = 0;
};


#endif //ROGUE_VISITOR_H
