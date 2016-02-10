//
// Created by Mark Jan Kamminga on 06-02-16.
//

#ifndef ROGUE_MST_H
#define ROGUE_MST_H

#include <iostream>
#include <list>
#include <set>
#include <map>
#include <vector>
#include "Room.h"

using namespace std;

class Mst {
public:
    Mst(int size) {
        this->size = size;
    }
    void addEdge(Room* from, Room* to, int distance);
    int find(Room* to);
    bool calc();
    bool isInSpanningTree(Room* from, Room* to);
    bool collapse(int num);
private:
    vector<pair<int, pair<Room*, Room*>>> pq;
    map<pair<Room*,Room*>, int> minimalSpanningTreePaths;
    map<pair<Room*, Room*>, int> excludedSanningTreePaths;
    map<Room*, int> typeLevels;
    map<int, vector<Room*>> levels;
    int currentLevel = -1;
    int size;
    bool calculated;
};

#endif //ROGUE_MST_H
