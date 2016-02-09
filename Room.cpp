//
// Created by alhric on 30-Oct-15.
//

#include <vector>
#include <queue>
#include "Room.h"
#include "Level.h"
#include "Items/Item.h"
#include <algorithm>
Room::Room (Level* level) {
    this->level = level;

    rooms["north"] = make_pair(-1, nullptr);
    rooms["south"] = make_pair(-1, nullptr);
    rooms["west"] = make_pair(-1, nullptr);
    rooms["east"] = make_pair(-1, nullptr);
}

void Room::setEdge (string direction, Room* edge, int distance) {
    if (direction == "north" ||
            direction == "east" ||
            direction == "south" ||
            direction == "west") {
        //on update
        if (!edges.empty()) {
            vector<Room *>::const_iterator position = find(edges.begin(), edges.end(), rooms[direction].second);

            if (position != edges.end()) {
                edges.erase(position);
            }
        }
        rooms[direction] = make_pair(distance, edge);
        edges.push_back(edge);
    }
}

Room* Room::getNorth(){
    return rooms["north"].second;
}

Room* Room::getWest(){
    return rooms["west"].second;
}

Room* Room::getEast(){
    return rooms["east"].second;
}

Room* Room::getSouth(){
    return rooms["south"].second;
}

int Room::getDistanceTo(Room* to) {
    for (auto room : rooms) {
        if (to == room.second.second) {
            return room.second.first;
        }
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

void Room::removeEdge(Room *edge) {
    for (auto it = edges.begin(); it != edges.end();  it++) {
        if (it.operator*() == edge) {
            edges.erase(it);
            break;
        }
    }
}

map<Room *, pair<int, Room *>> Room::getShortestPathToExit() {

    map<Room*, Room*> roomPath;
    deque<pair<int, Room*>> openPriorityQueue;
    map<Room*, pair<int, Room*>> closedList;

    openPriorityQueue.push_back(make_pair(0, this));
    roomPath[this] = this;
    Room* exitRoom = level->getExit();

    while (!openPriorityQueue.empty()) {
        Room* from = roomPath[openPriorityQueue.begin()->second];

        int distance = openPriorityQueue.begin()->first;
        Room* currentRoom = openPriorityQueue.begin()->second;

        closedList[currentRoom] = pair<int, Room*>{distance, from};

        if (currentRoom == exitRoom) {
            break;
        }

        openPriorityQueue.erase(openPriorityQueue.begin());

        auto edges = currentRoom->edges;

        for (auto it = edges.begin(); it != edges.end(); it++) {
            Room* edge = it.operator*();
            if (closedList.find(edge) == closedList.end()) {
                int relativeDistance = currentRoom->getDistanceTo(edge);

                auto position = find_if(openPriorityQueue.begin(), openPriorityQueue.end(), [&edge](std::pair<int, Room*> const& elem) {
                    return elem.second == edge;
                });
                //Room is in the openPriorityQueue and should be removed as the path from this room to the edge is the smallest possible distance
                if (position != openPriorityQueue.end()) {
                    int total = distance + relativeDistance;
                    if (total < position->first) {
                        closedList[edge] = make_pair(total, currentRoom);
                        openPriorityQueue.erase(position);
                    }
                } else {
                    openPriorityQueue.push_back(make_pair(distance + relativeDistance, edge));
                    roomPath[edge] = currentRoom;
                }
            }
        }

        sort(openPriorityQueue.begin(), openPriorityQueue.end());
    }

    return closedList;
}

void Room::addItem(Item *item) {
    itemsInRoom.push_back(item);
}

vector<Item*>* Room::getItems() {
    return  &itemsInRoom;
}

bool Room::isConnectedTo(Room *edge) {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        if (it.operator*() == edge) {
            return true;
        }
    }

    return false;
}
