//
// Created by alhric on 30-Oct-15.
//
#ifndef ROGUE_LEVEL_H
#define ROGUE_LEVEL_H

#include <iostream>
#include <list>
#include <set>
#include <map>
#include "Room.h"
#include <random>
#include <forward_list>
#include "Mst.h"

using namespace std;

class  Level {

public:
    Level(default_random_engine dist);
    void init(int x, int y);
    void setUp(int x, int y);
    void setPrevious(Level* level);
    void setNext(Level* level);
    Level* getNext();
    Room* getExit();

    virtual ~Level();

    Level* getPrevious();
    Room* getStartRoom();
    Room* getNorthEastRoom();
    bool isRoomInSpanningTree(Room* from, Room* to);
    Mst* getMst();

private:
    Level* previousLevel;
    Level* nextLevel;
    Room* exitRoom;
    Room* northEastRoom;
    Room** rooms = nullptr;
    map<pair<Room*,Room*>, int> minimalSpanningTreePaths;
    map<pair<Room*, Room*>, int> excludedSanningTreePaths;
    Mst* mst = nullptr;
    int totalRoomSize;
    int x;
    int y;
    random_device dev;
    default_random_engine dre;
    uniform_int_distribution<int> dist{1,20};
 };
#endif //ROGUE_LEVEL_H
