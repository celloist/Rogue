//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_EXITROOM_H
#define ROGUE_EXITROOM_H

#include "Room.h"

class Level;

using namespace std;

class ExitRoom : public Room {
public:
    ExitRoom (Level* level, string description) : Room(level, description){
        rooms["up"] = make_pair(-1, nullptr);
        rooms["down"] = make_pair(-1, nullptr);
    }
    virtual void setEdge (string direction, Room* edge, int distance);
    virtual bool isConnectedTo (Room* edge);
    virtual void accept(Visitor*);

private:
    bool initializedLevelEdges;
};

#endif //ROGUE_EXITROOM_H
