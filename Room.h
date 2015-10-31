//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H


class  Room{

public:
    Room();

    void setNorth(Room* room);
    void setWest(Room* room);
    void setEast(Room* room);
    void setSouth(Room* room);

    Room* getNorth();
    Room* getWest();
    Room* getEast();
    Room* getSouth();

private:
    Room* north  = nullptr;
    Room* west = nullptr;
    Room* east = nullptr;
    Room* south = nullptr;
};
#endif //ROGUE_ROOM_H
