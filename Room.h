//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H

#include <string>

using namespace std;
class Room{

public:
    Room(string id);
    void setNorth(Room* room);
    void setWest(Room* room);
    void setEast(Room* room);
    void setSouth(Room* room);
    void cleanUp();
    virtual ~Room();

    Room* getNorth();
    Room* getWest();
    Room* getEast();
    Room* getSouth();

private:
    string id;
    Room* north  = nullptr;
    Room* west = nullptr;
    Room* east = nullptr;
    Room* south = nullptr;
};

#endif //ROGUE_ROOM_H
