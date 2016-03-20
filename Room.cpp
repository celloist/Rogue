//
// Created by alhric on 30-Oct-15.
//

#include <vector>
#include <queue>
#include "Room.h"
#include "Level.h"

Room::Room (Level* level, string description) {
    this->level = level;
    this->description = description;

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

Room *Room::getByEdgeName(string name) {

    if (rooms.find(name) != rooms.end()){
        return rooms[name].second;
    }

    return nullptr;
}

int Room::getDistanceTo(Room* to) {
    for (auto room : rooms) {
        if (to == room.second.second) {
            return room.second.first;
        }
    }

    return -1;
}

int Room::getWeightTo(Room *to) {
    int weight = getDistanceTo(to);
    if (weight > 0) {
        for(auto it = to->enemiesInRoom.begin(); it != to->enemiesInRoom.end(); it++){
            weight+= it.operator*()->health;
        }

        if (to->trap != nullptr) {
            weight+= 30;
        }
    };

    return weight;
}

int Room::findRoom (Room* exit) {
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

            for (auto it = edges->rbegin(); it != edges->rend(); it++) {
                Room* roomToAdd = it.operator*();

                if (std::find(visited.begin(), visited.end(), roomToAdd) == visited.end()
                    && std::find(toSearch.begin(), toSearch.end(), roomToAdd)  == toSearch.end()) {

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

map<Room *, pair<int, Room *>> Room::getShortestPathToExit(Room* exitRoom) {
    map<Room*, Room*> roomPath;
    deque<pair<int, Room*>> openPriorityQueue;
    map<Room*, pair<int, Room*>> closedList;

    openPriorityQueue.push_back(make_pair(0, this));
    roomPath[this] = this;

    while (!openPriorityQueue.empty()) {
        Room* from = roomPath[openPriorityQueue.begin()->second];

        int weight = openPriorityQueue.begin()->first;
        Room* currentRoom = openPriorityQueue.begin()->second;

        closedList[currentRoom] = pair<int, Room*>{weight, from};

        if (currentRoom == exitRoom) {
            break;
        }

        openPriorityQueue.erase(openPriorityQueue.begin());

        auto edges = currentRoom->edges;

        for (auto it = edges.begin(); it != edges.end(); it++) {
            Room* edge = it.operator*();
            if (closedList.find(edge) == closedList.end()) {
                int relativeWeight = currentRoom->getWeightTo(edge);

                auto position = find_if(openPriorityQueue.begin(), openPriorityQueue.end(), [&edge](std::pair<int, Room*> const& elem) {
                    return elem.second == edge;
                });
                //Room is in the openPriorityQueue and should be removed as the path from this room to the edge is the smallest possible distance
                if (position != openPriorityQueue.end()) {
                    int total = weight + relativeWeight;
                    if (total < position->first) {
                        closedList[edge] = make_pair(total, currentRoom);
                        openPriorityQueue.erase(position);
                    }
                } else {
                    openPriorityQueue.push_back(make_pair(weight + relativeWeight, edge));
                    roomPath[edge] = currentRoom;
                }
            }
        }

        sort(openPriorityQueue.begin(), openPriorityQueue.end());
    }

    return closedList;
}

void Room::setTrap(Trap *trap) {
    this->trap = trap;
}

bool Room::hasTrap() {
    return this->trap != nullptr;
}

void Room::addItem(Item* item) {
    itemsInRoom.push_back(item);
}

void Room::removeItem(Item *item) {
    auto pos = find(itemsInRoom.begin(), itemsInRoom.end(), item);
    if (pos != itemsInRoom.end()) {
        itemsInRoom.erase(pos);
    }
}

vector<Item*>* Room::getItems() {
    return &itemsInRoom;
}

vector<Enemy*>* Room::getEnemies() {
    return &enemiesInRoom;
}

bool Room::isConnectedTo(Room *edge) {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        if (it.operator*() == edge) {
            return true;
        }
    }

    return false;
}

void Room::addEnemy(Enemy *enemy) {
    enemiesInRoom.push_back(enemy);
}

void Room::removeEnemy(Enemy *enemy) {
    auto it = find(enemiesInRoom.begin(), enemiesInRoom.end(), enemy);

    if (it != enemiesInRoom.end()) {
        enemiesInRoom.erase(it);
    }
}

void Room::moveinHero(Hero *hero) {
    this->hero = hero;

    if (!visited) {
        visited = true;
    }
}

void Room::moveoutHero() {
    hero = nullptr;
}

bool Room::hasBeenVisited() {
    return visited;
}

Level *Room::getLevel() {
    return level;
}

void Room::accept(Visitor* v){
    v->visit(this);
}

string Room::getDescription() {
    return description;
}
