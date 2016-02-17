//
// Created by alhric on 30-Oct-15.
//

#include <list>
#include <random>
#include "Level.h"
#include "Game.h"

Level::Level (default_random_engine dre, int x, int y, Game* game) {
    this->dre = dre;
    this->x = x;
    this->y = y;
    this->game = game;
};

void Level::init() {
    if (!initialized) {
        int num = x * y;
        totalRoomSize = num;
        mst = new Mst{totalRoomSize};


        rooms = new Room *[num];
        int i = 0;

        uniform_int_distribution<int> roomdist{0, num - 1};
        int exitRoomIndex = 0;//roomdist(dre);
        while (i < num) {
            if (i != exitRoomIndex) {
                rooms[i] = new Room{this};
            } else {
                rooms[i] = new ExitRoom{this};
            }
            if (i % x > 0) {
                int westEastNum = dist(dre);
                rooms[i]->setEdge("west", rooms[i - 1], westEastNum);
                rooms[i - 1]->setEdge("east", rooms[i], westEastNum);
                mst->addEdge(rooms[i - 1], rooms[i], westEastNum);
            }

            int top = i - x;

            if (top >= 0) {
                int southwestNum = dist(dre);
                Room *r = rooms[i];
                rooms[top]->setEdge("south", rooms[i], southwestNum);
                rooms[i]->setEdge("north", rooms[top], southwestNum);
                mst->addEdge(rooms[top], rooms[i], southwestNum);
            }

            i++;
        }

        northEastRoom = rooms[0];
        exitRoom = rooms[num - 1];

        initialized = true;
    }
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
    if (nextLevel) {
        nextLevel->init();
    }
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

void Level::setAsCurrentLevel() {
    game->setCurrentLevel(this);
}
