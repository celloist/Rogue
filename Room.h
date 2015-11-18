//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H

#include <string>
#include <map>
#include <vector>
#include <unordered_map>

class Level;

using namespace std;
class Room{

public:
    Room(Level* level);
    void setEdge (string direction, Room* edge, int distance);
    int getDistanceTo(Room* to);

    Room* getNorth();
    Room* getWest();
    Room* getEast();
    Room* getSouth();
    int findExitRoom();
    map<Room *, pair<int, Room *>> getShortestPathToExit();
    vector<Room*>* getEdges();

private:
    Level* level;
    unordered_map<string, pair<int, Room*>> rooms;
    vector<Room*> edges;
};

#endif //ROGUE_ROOM_H
