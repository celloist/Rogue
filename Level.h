//
// Created by alhric on 30-Oct-15.
//
#ifndef ROGUE_LEVEL_H
#define ROGUE_LEVEL_H

#include <iostream>
#include <list>
#include <set>
#include <map>
#include <random>
#include <forward_list>
#include "Mst.h"
#include "Room.h"
#include "ExitRoom.h"

class Game;

using namespace std;

class Level {

public:
    Level(default_random_engine dist, int x, int y, Game* game);
    void init();
    void setPrevious(Level* level);
    void setNext(Level* level);
    void setAsCurrent();
    Level* getNext();
    Room* getExit();

    virtual ~Level();

    Level* getPrevious();
    Room* getStartRoom();
    Room* getNorthEastRoom();
    bool isRoomInSpanningTree(Room* from, Room* to);
    Mst* getMst();
    void setAsCurrentLevel();

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
    bool initialized;
    random_device dev;
    default_random_engine dre;
    uniform_int_distribution<int> dist{1,20};
    Game* game;
 };
#endif //ROGUE_LEVEL_H
