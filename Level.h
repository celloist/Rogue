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

using namespace std;

class  Level {

public:
    Level();
    void init(int x, int y);
    void setUp(int x, int y);
    void setDistances();
    void setPrevious(Level* level);
    void setNext(Level* level);
    void cleanUp();
    void addRoomToPQ(vector<pair<Room*, Room*>> *pq, vector<Room*>* visited, Room* from,  Room* to);
    Level* getNext();
    Room* getExit();

    virtual ~Level();

    Level* getPrevious();
    Room* getStartRoom();
    Room* getNorthEastRoom();
    bool isRoomInSPanningTree(Room* current, Room* to);


private:
    Level* previousLevel;
    Level* nextLevel;
    Room* startRoom;
    Room* exitRoom;
    Room* northEastRoom;
    Room** rooms = nullptr;
    map<pair<Room*, Room*>, Room*> minimalSpanningTree;
    int totalRoomSize;
    int x;
    int y;
    random_device dev;
    default_random_engine dre;
    uniform_int_distribution<int> dist{1,20};
    void setRoomDistanceToRandomly (Room* roomFrom, Room* roomTo);
    void calcPrimMinSpanTree();
};
#endif //ROGUE_LEVEL_H
