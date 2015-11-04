//
// Created by alhric on 30-Oct-15.
//

#include <vector>
#include <queue>
#include "Room.h"
#include "Level.h"
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
        std::remove(edges.begin(), edges.end(), roomToupdate);
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

Room* Room::findExitRoom () {
    Room* exit = level->getExit();

    vector<Room*> visited;
    std::deque<Room*> toSearch;
    toSearch.push_front(this);

    while (!toSearch.empty()) {
        Room* currentRoom = toSearch.front();
        toSearch.pop_front();
        vector<Room*> visited;

        if (currentRoom == exit) {
            //todo found room!!! Yeah!
            break;
        } else {
            vector<Room*>::iterator it;
            for (auto it = visited.begin(); it != visited.end(); ++it) {
                Room* roomToAdd = it.operator*();
                if (std::find(visited.begin(), visited.end(), roomToAdd) == visited.end()
                    && std::find(toSearch.begin(), toSearch.end(), roomToAdd) == toSearch.end()) {
                    toSearch.push_back(roomToAdd);
                }
            }
        }

    }

    return nullptr;
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
