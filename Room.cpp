//
// Created by alhric on 30-Oct-15.
//

#include "Room.h"


void Room::setNorth(Room* room){
    north = room;

    if (north != nullptr) {
        room->setSouth(this);
    }
}

void Room::setWest(Room* room) {
    west = room;
    if (west != nullptr) {
        west->setEast(this);
    }
}

void Room::setEast(Room* room) {
    east = room;

    if (east != nullptr) {
        east->setWest(this);
    }
}

void Room::setSouth(Room* room) {
    south = room;

    if (south != nullptr) {
        south->setNorth(this);
    }
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