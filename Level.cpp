//
// Created by alhric on 30-Oct-15.
//

#include <list>
#include <random>
#include "Level.h"

Level::Level (default_random_engine dre) {
    this->dre = dre;
};

void Level::init(int x, int y) {
    setUp(x,y);
}

void Level::setUp(int x, int y) {
    int num = x*y;
    totalRoomSize = num;
    mst = new Mst{totalRoomSize};

    this->x = x;
    this->y = y;

    rooms = new Room*[num];
    int i = 0;

    while (i < num) {
        rooms[i] = new Room{this};

        if (i % x > 0) {
            int westEastNum = dist(dre);
            rooms[i]->setEdge("west", rooms[i -1], westEastNum);
            rooms[i-1]->setEdge("east", rooms[i], westEastNum);
            mst->addEdge(rooms[i -1], rooms[i], westEastNum);
        }

        int top = i- x;

        if (top >= 0){
            int southwestNum = dist(dre);
            Room* r = rooms[i];
            rooms[top]->setEdge("south", rooms[i], southwestNum);
            rooms[i]->setEdge("north", rooms[top], southwestNum);
            mst->addEdge(rooms[top], rooms[i], southwestNum);
        }

        i++;
    }

    northEastRoom = rooms[0];
    exitRoom = rooms[num -1];
}

bool Level::isRoomInSpanningTree(Room* from, Room* to) {
    return mst->isInSpanningTree(from, to);
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

Level::~Level() {
    if (rooms != nullptr) {
        for (int i = totalRoomSize - 1; i > 0; i--) {
            delete rooms[i];
        }

        delete[] rooms;
        delete mst;
    }
}

Mst *Level::getMst() {
    return mst;
}
