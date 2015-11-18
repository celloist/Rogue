//
// Created by alhric on 30-Oct-15.
//

#include <list>
#include <random>
//#include <altivec.h>
#include "Level.h"
#include <algorithm>
#include <forward_list>
#include <deque>

Level::Level () {

};

void Level::init(int x, int y) {
    setUp(x,y);
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
        rooms[i] = new Room{this};

        if (i % x > 0) {
            int westEastNum = dist(dre);
            rooms[i]->setEdge("west", rooms[i -1], westEastNum);
            rooms[i-1]->setEdge("east", rooms[i], westEastNum);
        }

        int top = i- x;

        if (top >= 0){
            int southwestNum = dist(dre);
            Room* r = rooms[i];
            rooms[top]->setEdge("south", rooms[i], southwestNum);
            rooms[i]->setEdge("north", rooms[top], southwestNum);
        }

        i++;
    }

    northEastRoom = rooms[0];
    exitRoom = rooms[num -1];

}

void Level::calcPrimMinSpanTree () {
    forward_list<pair<int, pair<Room*, Room*>>> pq;
    map<Room*, int> mst;
    for (int i = 0; i< totalRoomSize; i++) {
        Room* vector = rooms[i];
        Room* edge = nullptr;
        if (vector->getSouth() != nullptr){
            edge = vector->getSouth();
            int distance = vector->getDistanceTo(edge);
            pq.push_front(pair<int, pair<Room *, Room *>>{distance, {vector, edge}});

        }

        if (vector->getWest() != nullptr){
            edge = vector->getWest();
            int distance = vector->getDistanceTo(edge);
            pq.push_front(pair<int, pair<Room *, Room *>>{distance, {vector, edge}});
        }
    }

    pq.sort();

    int num = 1;
    while (!pq.empty() && num != totalRoomSize){
        int distance = pq.begin()->first;
        Room* from = pq.begin()->second.first;
        Room* to = pq.begin()->second.second;
        pq.pop_front();
        Room* point = nullptr;

        if (mst.find(to) == mst.end()) {
            point = to;
        } else if (mst.find(from) == mst.end()) {
            point = from;
        }

        if (point != nullptr){
            mst[point] = distance;
            minimalSpanningTree[pair<Room*, Room*> {from, to}] = distance;
            minimalSpanningTree[pair<Room*, Room*> {to, from}] = distance;
            num++;
        }
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

Level::~Level() {
    if (rooms != nullptr) {
        for (int i = totalRoomSize - 1; i > 0; i--) {
            delete rooms[i];
        }

        delete[] rooms;
    }
}