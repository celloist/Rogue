//
// Created by alhric on 30-Oct-15.
//

#include <list>
#include <random>
#include "Level.h"
#include "Game.h"

Level::Level (default_random_engine& dre, int x, int y) {
    if (x * y < 8) {
        throw invalid_argument("not enough rooms: minimum requirement of eight not met");
    }
    this->dre = dre;
    this->x = x;
    this->y = y;
};

void Level::init(LevelDescritions& ld, vector<Enemy*>& enemies, vector<Item*> items, vector<Item*> traps) {
    int num = x * y;
    totalRoomSize = num;
    mst = new Mst{totalRoomSize};
    rooms = new Room *[num];
    int i = 0;

    uniform_int_distribution<int> roomdist{0, num - 1};
    //Assign rooms indexs randomly
    int exitRoomIndex = roomdist(dre);
    int stairsUpRoomIndex = roomdist(dre);
    int startRoomIndex = roomdist(dre);

    while (i < num) {
        string roomDescription = createRoomDescription(ld);
        if (i != exitRoomIndex && i != stairsUpRoomIndex) {
            rooms[i] = new Room{this, roomDescription};
        } else {
            rooms[i] = new ExitRoom{this, roomDescription};
        }

        if (i % x > 0) {
            setRoomByIndex("east", i, "west", i-1);
        }

        int top = i - x;

        if (top >= 0) {
            setRoomByIndex("north", top, "south", i);
        }

        i++;
    }

    northEastRoom = rooms[0];
    exitRoom = rooms[exitRoomIndex];
    roomUp = rooms[stairsUpRoomIndex];
    startRoom = rooms[startRoomIndex];

    assignEnemiesRadomly(enemies, roomdist);
    assignItemsRadomly(items, roomdist);
    assignTraps(traps, roomdist);
}

void Level::setRoomByIndex(string edgeFrom, int indexFrom, string edgeTo, int indexTo){
    int distance = dist(dre);
    rooms[indexFrom]->setEdge(edgeTo, rooms[indexTo], distance);

    rooms[indexTo]->setEdge(edgeFrom, rooms[indexFrom], distance);
    mst->addEdge(rooms[indexTo], rooms[indexFrom], distance);
}

string Level::getRandomDescription(vector<string> &item) {
    int size = (item.size() - 1);

    if (size <= 0) {
        return "";
    }

    uniform_int_distribution<int> randItem{0, size};

    return item.at(randItem(dre));
}

string Level::createRoomDescription(LevelDescritions &descritions) {
    return "Het is een "+ getRandomDescription(descritions.sizes)
            + " " + getRandomDescription(descritions.tidyness)
            + " ruimte, met in het midden een " + getRandomDescription(descritions.furniture)
            + "; aan de wand hangt een "+ getRandomDescription(descritions.decorations) +".\n"
            + "De ruimte wordt verlicht door een "+ getRandomDescription(descritions.lightsources) + ".\n"
            + "Op de achtergrond hoor je "+ getRandomDescription(descritions.sounds)
            + " en af en toe valt er een "+ getRandomDescription(descritions.misc) + ".";
}

void Level::assignEnemiesRadomly(vector<Enemy*> &enemies, uniform_int_distribution<int>& roomdist) {
    if (enemies.size() > 0) {
        auto it = enemies.begin();
        while (it != enemies.end()) {
            Enemy *enemy = it.operator*();
            int index = roomdist(dre);

            if (rooms[index] != startRoom) {
                rooms[index]->addEnemy(enemy);
                it++;
            }
        }
    }
}

void Level::assignItemsRadomly(vector<Item *> &items, uniform_int_distribution<int> &dist) {
    if (items.size() > 0) {
        for (auto it = items.begin(); it != items.end(); it++) {
            Item *item = it.operator*();
            int index = dist(dre);
            rooms[index]->addItem(item);
        }
    }
}

void Level::assignTraps(vector<Item *>& traps, uniform_int_distribution<int> &dist) {
    if (traps.size() > 0) {
        auto it = traps.begin();
        while (it != traps.end()) {
            Trap* trap = dynamic_cast<Trap*>(it.operator*());

            int index = dist(dre);

            if (rooms[index] != startRoom && !rooms[index]->hasTrap()) {
                rooms[index]->setTrap(trap);
                it++;
            }
        }
    }
}

bool Level::isRoomInSpanningTree(Room* from, Room* to) {
    return mst->isInSpanningTree(from, to);
}

void Level::setPrevious(Level *level) {
    previousLevel = level;
    if (level) {
        roomUp->setEdge("up", level->getStartRoom(), 0);
        if (level->nextLevel != this) {
            level->setNext(this);
        }
    }
}

void Level::setNext(Level *level) {
    nextLevel = level;

    if (level) {
        exitRoom->setEdge("down", level->getStartRoom(), 0);

        if (level->previousLevel != this) {
            level->setPrevious(this);
        }
    }
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
    if (!mst->isCalculated()) {
        mst->calc();
    }
    return mst;
}

Room *Level::getStairsUpRoom() {
    return roomUp;
}

Room *Level::getStartRoom() {
    return startRoom;
}