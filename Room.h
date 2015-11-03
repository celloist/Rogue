//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H

#include <string>
#include <map>

using namespace std;
class Room{

public:
    void setNorth(Room* room);
    void setWest(Room* room);
    void setEast(Room* room);
    void setSouth(Room* room);
    void cleanUp();
    void setDistanceTo (Room* roomFrom, Room* to, int distance);
    virtual ~Room();

    Room* getNorth();
    Room* getWest();
    Room* getEast();
    Room* getSouth();


private:
    Room* north  = nullptr;
    Room* west = nullptr;
    Room* east = nullptr;
    Room* south = nullptr;
    map<pair<Room*, Room*>, int> distanaces;
};

#endif //ROGUE_ROOM_H
