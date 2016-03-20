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
struct LevelDescritions;

using namespace std;

class Level {

public:
    Level(default_random_engine& dist, int x, int y);
    void init(LevelDescritions&);
    void setPrevious(Level* level);
    void setNext(Level* level);
    Level* getNext();
    Room* getExit();
    Room* getStairsUpRoom();

    virtual ~Level();

    Level* getPrevious();
    Room* getStartRoom();
    Room* getNorthEastRoom();
    bool isRoomInSpanningTree(Room* from, Room* to);
    Mst* getMst();

private:
    Level* previousLevel;
    Level* nextLevel;
    Room* roomUp = nullptr;
    Room* exitRoom = nullptr;
    Room* northEastRoom;
    Room* startRoom = nullptr;
    Room** rooms = nullptr;
    Mst* mst = nullptr;
    vector<Trap*> traps;
    int totalRoomSize;
    int x;
    int y;
    bool initialized = false;
    random_device dev;
    default_random_engine dre;
    uniform_int_distribution<int> dist{1,20};

    void setRoomByIndex(string edgeFrom, int indexFrom, string edgeTo, int indexTo);
    string getRandomDescription(vector<string>& item);
    string createRoomDescription(LevelDescritions&);

 };
#endif //ROGUE_LEVEL_H
