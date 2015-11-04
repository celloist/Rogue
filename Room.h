//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H

#include <string>
#include <map>
#include <vector>
class Level;

using namespace std;
class Room{

public:
    Room(Level* level);
    void setEdge (string direction, Room* edge);
    void setNorth(Room* room);
    void setWest(Room* room);
    void setEast(Room* room);
    void setSouth(Room* room);
    void cleanUp();
    void setDistanceTo (Room* to, int distance);
    int getDistanceTo(Room* to);
    virtual ~Room();

    Room* getNorth();
    Room* getWest();
    Room* getEast();
    Room* getSouth();
    Room* findExitRoom();
    Room* getShortestPathTo();
    vector<Room*>* getEdges();

private:
    Room* north  = nullptr;
    Room* west = nullptr;
    Room* east = nullptr;
    Room* south = nullptr;
    map<Room*, int> distanaces;
    Level* level;
    vector<Room*> edges;
};

#endif //ROGUE_ROOM_H
