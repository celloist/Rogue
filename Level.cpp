//
// Created by alhric on 30-Oct-15.
//

#include <list>
#include <random>
//#include <altivec.h>
#include "Level.h"
#include <algorithm>
#include <forward_list>

Level::Level () {

};

void Level::init(int x, int y) {
    setUp(x,y);
    setDistances();
    calcPrimMinSpanTree();
}

void Level::setUp(int x, int y) {
    int num = x*y;
    totalRoomSize = num;

    this->x = x;
    this->y = y;

    rooms = new Room*[num];
    int i = 0;

    while (i < num) {
        rooms[i] = new Room{this};
        if (i % x > 0) {
            rooms[i]->setEdge("west", rooms[i -1]);
            rooms[i-1]->setEdge("east", rooms[i]);
        }

        int top = i- x;

        if (top >= 0){
            Room* r = rooms[i];
            rooms[top]->setEdge("south", rooms[i]);
            rooms[i]->setEdge("north", rooms[top]);
        }

        i++;
    }

    northEastRoom = rooms[0];
    exitRoom = rooms[num-1];

}

void Level::setDistances () {
    int i = 0;
    while (i < totalRoomSize) {
        int top = i - x;

        if (i % x > 0) {
            setRoomDistanceToRandomly(rooms[i], rooms[(i -1)]);
        }

        if (top >= 0) {
            setRoomDistanceToRandomly(rooms[i], rooms[top]);
        }
        i++;
    }
}

void Level::setRoomDistanceToRandomly (Room* roomFrom, Room* roomTo) {
    int num = dist(dre);

    roomFrom->setDistanceTo(roomTo, num);
    roomTo->setDistanceTo(roomFrom, num);
}

void Level::calcPrimMinSpanTree () {
    vector<Room *>* pq = nullptr;
    for (int i = 0; i < totalRoomSize; i++) {
        Room* vector = rooms[i];

        pq = vector->getEdges();
        Room* smallestRoom = nullptr;
        int leastDistance = -1;
        for (auto edgeIt = pq->begin(); edgeIt != pq->end(); ++edgeIt) {
            auto edge = edgeIt.operator*();

            int distance = vector->getDistanceTo(edge);
            if (smallestRoom == nullptr || distance < leastDistance) {
                smallestRoom = edge;
                leastDistance = distance;
            }
        }

        minimalSpanningTree[pair<Room*, Room*> {vector, smallestRoom}] = smallestRoom;
    }
}

bool Level::isRoomInSPanningTree(Room* current, Room* to) {
    pair<Room*, Room*> key {current, to};
    return minimalSpanningTree.find(key) != minimalSpanningTree.end();
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

Room* Level::getExit() {
    return exitRoom;
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