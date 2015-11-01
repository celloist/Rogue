//
// Created by alhric on 30-Oct-15.
//

#include "Room.h"

Room::Room(string id) {
    this->id = id;
}
void Room::setNorth(Room* room){
    north = room;
}

void Room::setWest(Room* room) {
    west = room;
}

void Room::setEast(Room* room) {
    east = room;
}

void Room::setSouth(Room* room) {
    south = room;
}

Room* Room::getNorth(){
    return north;
}

Room* Room::getWest(){
    return west;
}

Room* Room::getEast(){
    return east;
}

Room* Room::getSouth(){
    return south;
}

void Room::cleanUp(){
    north = nullptr;
    south = nullptr;
    west = nullptr;
    east = nullptr;
}

Room::~Room(){
    cleanUp();

    delete north;
    delete south;
    delete west;
    delete east;
}
