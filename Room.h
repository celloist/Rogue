//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ROOM_H
#define ROGUE_ROOM_H

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include "Items/Item.h"
#include "Characters/Enemy.h"
#include "ItemVisitable.h"
#include "Items/Trap.h"

class Level;

using namespace std;
class Room : ItemVisitable{

public:
    Room(Level* level, string description);
    virtual void setEdge (string direction, Room* edge, int distance);
    void removeEdge(Room* edge);
    int getDistanceTo(Room* to);
    int getWeightTo(Room* to);

    virtual Room* getByEdgeName(string name);

    virtual bool isConnectedTo (Room* edge);
    int findRoom (Room* exit);
    map<Room *, pair<int, Room *>> getShortestPathToExit(Room* exitRoom);
    vector<Room*>* getEdges();
    void addItem(Item* item);
    void removeItem(Item* item);
    vector<Item *> * getItems();
    void setTrap(Trap* trap);
    bool hasTrap();
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);
    vector<Enemy*>* getEnemies();
    virtual void moveinHero(Hero* hero);
    void moveoutHero();
    bool hasBeenVisited();
    Level* getLevel();
    virtual void accept(Visitor*);
    string getDescription();
private:
    vector<Room*> edges;
    vector<Item*> itemsInRoom;
    vector<Enemy*> enemiesInRoom;
    bool visited = false;
    Trap* trap = nullptr;
    string description;

protected:
    Hero* hero = nullptr;
    Level* level;
    unordered_map<string, pair<int, Room*>> rooms;
};

#endif //ROGUE_ROOM_H
