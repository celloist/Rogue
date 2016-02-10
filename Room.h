//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include "Items/Item.h"
#include "Characters/Enemy.h"

class Level;

using namespace std;
class Room{

public:
    Room(Level* level);
    void setEdge (string direction, Room* edge, int distance);
    void removeEdge(Room* edge);
    int getDistanceTo(Room* to);

    Room* getNorth();
    Room* getWest();
    Room* getEast();
    Room* getSouth();

    bool isConnectedTo (Room* edge);
    int findExitRoom();
    map<Room *, pair<int, Room *>> getShortestPathToExit();
    vector<Room*>* getEdges();
    void addItem(Item* item);
    vector<Item *> * getItems();
    vector<Enemy*> * getEnemies();

private:
    Level* level;
    unordered_map<string, pair<int, Room*>> rooms;
    vector<Room*> edges;
    vector<Item*> itemsInRoom;
    vector<Enemy*> enemiesInRoom;
};

#endif //ROGUE_ROOM_H
