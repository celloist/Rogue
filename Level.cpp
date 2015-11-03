//
// Created by alhric on 30-Oct-15.
//

#include <list>
#include <random>
#include "Level.h"

void Level::init(int x, int y) {
    setUp(x,y);
    setDistances();
    //calcPrimMinSpanTree();
}

void Level::setUp(int x, int y) {
    int num = x*y;
    totalRoomSize = num;

    this->x = x;
    this->y = y;

    rooms = new Room*[num];
    int i = 0;
    while (i < num) {
        rooms[i] = new Room{};

        if (i % y > 0) {
            rooms[i]->setWest(rooms[i -1]);
            rooms[i-1]->setEast(rooms[i]);
        }

        int top = i- y;

        if (top >= 0){
            rooms[top]->setSouth(rooms[i]);
            rooms[i]->setNorth(rooms[top]);
        }

        i++;
    }

    northEastRoom = rooms[0];
}

void Level::setDistances () {
    int i = 0;
    while (i < totalRoomSize) {
        int top = i - y;

        if (i % y > 0) {
            setRoomDistanceToRandomly(i, (i -1));
        }

        if (top > 0) {
            setRoomDistanceToRandomly(i, top);
        }
        i++;
    }
}

void Level::setRoomDistanceToRandomly (int roomFrom, int roomTo) {
    int num = dist(dre);

}

int Level::getRoomDistanceTo (Room* fromRoom, Room* toRoom) {
    pair<Room*, Room*> key1;
    pair<Room*, Room*> key2;

    key1.first = fromRoom;
    key1.second = toRoom;

    key2.first = toRoom;
    key2.second = fromRoom;


    if (distanaces.count(key1) > 0) {
        return distanaces.at(key1);
    } else if (distanaces.count(key2) > 0 ) {
        distanaces.at(key2);
    } else {
        return -1;
    }
}

void Level::calcPrimMinSpanTree () {
    set<Room*> visited;
    set<Room*,set<Room*>> path;
    set<Room*> pq;

    Room* current = northEastRoom;


    while (visited.size() != totalRoomSize) {
        visited.insert(*&current);

        if (current->getSouth() != nullptr && visited.count(current->getSouth()) == 0) {
            pq.insert(current->getSouth());
        }

        if (current->getNorth() != nullptr && visited.count(current->getNorth()) == 0) {
            pq.insert(current->getNorth());
        }

        if (current->getWest() != nullptr && visited.count(current->getWest()) == 0) {
            pq.insert(current->getWest());
        }

        if (current->getEast() != nullptr && visited.count(current->getEast()) == 0) {
            pq.insert(current->getEast());
        }
    }
}

void Level::setPrevious(Level *level) {
    previousLevel = level;
    if (level) {
        level->setNext(this);
    }
}

void Level::setNext(Level *level) {
    nextLevel = level;
}

Level* Level::getNext() {
 return nextLevel;
}

Level* Level::getPrevious() {
 return previousLevel;
}

Room* Level::getNorthEastRoom() {
    return northEastRoom;
}

void Level::cleanUp () {
    northEastRoom = nullptr;
    previousLevel = nullptr;
    nextLevel = nullptr;
}

Level::~Level() {
    cleanUp();

    if (rooms != nullptr) {
        for (int i = totalRoomSize - 1; i > 0; i--) {
            delete rooms[i];
        }

        delete northEastRoom;
        delete previousLevel;
        delete nextLevel;

        delete[] rooms;
    }
}
