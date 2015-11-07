//
// Created by alhric on 30-Oct-15.
//

#include <list>
#include <random>
//#include <altivec.h>
#include "Level.h"
#include <algorithm>
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
    vector<Room*> visited;

    Room* current = northEastRoom;
    vector<pair<Room*, Room*>> pq;
    bool equals = rooms[0] == current;

    while (current != nullptr && visited.size() != totalRoomSize) {
        visited.push_back(*&current);

        vector<Room*>* edges = current->getEdges();
        //Add all edges connected to the current vertex,  if they havent been visted or don't point to a visited vertex
        for(auto it = edges->begin(); it != edges->end(); ++it) {
            Room* to = it.operator*();
            if (to != nullptr && std::find(visited.begin(), visited.end(), to) == visited.end()) {
                pair<Room *, Room *> fromTo;
                fromTo.first = current;
                fromTo.second = to;
                pq.push_back(fromTo);
            }
        }

        Room* nextRoom = nullptr;
        Room* fromRoom = nullptr;
        int smallestDistance = -1;
        int smallestIndex = -1;
        int index = 0;

        for(auto it = pq.begin(); it != pq.end(); ++it) {
            Room* from = it->first;
            Room* to = it->second;
            int distance = from->getDistanceTo(to);
            if (distance >= 0 && (distance < smallestDistance || smallestDistance == -1)
                && std::find(visited.begin(), visited.end(), to) == visited.end()) {
                fromRoom = from;
                nextRoom = to;
                smallestDistance = distance;
                smallestIndex = index;
            }
            index++;
        }
        //Verwijder de kleinste gevonden vertex
        if (smallestIndex >= 0) {
            pair<Room*, Room*> key1 {fromRoom, nextRoom};
            pair<Room*, Room*> key2 {nextRoom, fromRoom};

            minimalSpanningTree[key1] = nextRoom;
            minimalSpanningTree[key2] = fromRoom;

            pq.erase(pq.begin() + smallestIndex, pq.begin() + smallestIndex);
        }

        current = nextRoom;
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