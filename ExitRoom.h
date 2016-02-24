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
    ExitRoom (Level* level) : Room(level){
        rooms["up"] = make_pair(-1, nullptr);
        rooms["down"] = make_pair(-1, nullptr);
    }

    virtual bool isConnectedTo (Room* edge);
    virtual Room* getByEdgeName(string name);
    virtual void moveinHero(Hero *hero);
    virtual void accept(Visitor*);

private:
    void init();
    bool initializedLevelEdges;
};

#endif //ROGUE_EXITROOM_H
