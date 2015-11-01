//
// Created by alhric on 30-Oct-15.
//

#include <list>
#include <random>
#include "Level.h"

void Level::init(int x, int y) {
    setUp(x,y);
    setDistances();
}

void Level::setUp(int x, int y) {
    int num = x*y;
    size = num;
    rooms = new Room*[num];
    int i = 0;
    char prefix = 'A';
    while (i < num) {
        string id = to_string(prefix) + ":" + to_string(((i + 1) % y));
        rooms[i] = new Room{id};

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
    random_device dev;
    default_random_engine dre{dev()};
    uniform_int_distribution<int> dist{1, 30};
    Room* current = northEastRoom;
    while (current) {
        /*if (current->getSouth() != nullptr) {
            pair<Room, Room> connection;
            make_pair(*current, *current->getSouth());
            distanaces[connection] = dist(dre);
        }*/

        current = current->getSouth();

        if (current){
            current = current->getSouth();
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
        for (int i = size - 1; i > 0; i--) {
            delete rooms[i];
        }

        delete northEastRoom;
        delete previousLevel;
        delete nextLevel;

        delete[] rooms;
    }
}
