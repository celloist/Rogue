//
// Created by alhric on 30-Oct-15.
//
#include <iostream>
#include <list>
#include <set>
#include <map>
#include "Room.h"

#ifndef ROGUE_LEVEL_H
#define ROGUE_LEVEL_H

using namespace std;

class  Level {

public:
    void init(int x, int y);
    void setUp(int x, int y);
    void setDistances();
    void setPrevious(Level* level);
    void setNext(Level* level);
    void cleanUp();
    Level* getNext();

    virtual ~Level();

    Level* getPrevious();
    Room* getStartRoom();
    Room* getNorthEastRoom();

private:
    Level* previousLevel;
    Level* nextLevel;
    Room* startRoom;
    Room* northEastRoom;
    Room** rooms;
    map<pair<Room*, Room*>, int> distanaces;
    int size;
};
#endif //ROGUE_LEVEL_H
