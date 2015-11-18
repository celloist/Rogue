//
// Created by alhric on 30-Oct-15.
//

#include <vector>
#include <queue>
#include "Room.h"
#include "Level.h"
#include <algorithm>
Room::Room (Level* level) {
    this->level = level;
}

void Room::setEdge (string direction, Room* edge) {
    Room* roomToupdate;

    if (direction == "north") {
        roomToupdate = north;
        north = edge;
    } else if (direction == "east") {
        roomToupdate = east;
        east = edge;
    } else if (direction == "south") {
        roomToupdate = south;
        south = edge;
    } else if (direction == "west") {
        roomToupdate = west;
        west = edge;
    }

    //Verwijder edge van de edges als deze wordt geupdate
    if (roomToupdate != nullptr) {
        remove(edges.begin(), edges.end(), roomToupdate);
    }
    //Voeg edge toe als deze een waarde heeft
    if (edge != nullptr) {
        edges.push_back(edge);
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

void Room::setDistanceTo (Room* roomTo, int distance) {
    distanaces[roomTo] = distance;
}

int Room::getDistanceTo(Room* to) {
    if (distanaces.find(to) != distanaces.end() ) {
        return distanaces[to];
    }

    return -1;
}

int Room::findExitRoom () {
    Room* exit = level->getExit();

    vector<Room*> visited;
    std::deque<Room*> toSearch;
    toSearch.push_back(this);
    Room* currentRoom = nullptr;
    map<Room*, int> searchLevels;
    searchLevels[this] = 0;

    int levelToReturn = -1;

    while (!toSearch.empty()) {
        currentRoom = toSearch.front();

        toSearch.pop_front();

        if (currentRoom == exit) {
            levelToReturn = searchLevels[currentRoom];
            break;
        } else {

            visited.push_back(currentRoom);
            vector<Room*>* edges = currentRoom->getEdges();
            int level = searchLevels[currentRoom];
            searchLevels.erase(currentRoom);

            for (auto it = edges->rbegin(); it != edges->rend(); ++it) {
                Room* roomToAdd = it.operator*();

                if (std::find(visited.rbegin(), visited.rend(), roomToAdd) == visited.rend()
                    && std::find(toSearch.rbegin(), toSearch.rend(), roomToAdd)  == toSearch.rbegin()) {

                    toSearch.push_back(roomToAdd);
                    searchLevels[roomToAdd] = level + 1;
                }
            }
        }
    }

    return levelToReturn;
}

vector<Room*>* Room::getEdges() {
    return &edges;
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

string Room::getShortestPathToExit() {
    string path = "";
    map<Room*,int> shortestPathTo;
    Room* exitRoom = level->getExit();
    Room* currentRoom = this;
    while(currentRoom != exitRoom)
    {

    }
    return path;
}

void Room::addItem(Item *item) {
    itemsInRoom.push_back(item);
}

vector<Item*>* Room::getItems() {
    return  &itemsInRoom;
}
