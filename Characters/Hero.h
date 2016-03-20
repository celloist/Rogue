//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_HERO_H
#define ROGUE_HERO_H

#include <vector>
#include "AbstractCharacter.h"
#include "iostream"
#include "../Room.h"
#include "../Views/ConsoleInputOutput.h"

class Item;

using namespace std;

class Hero : public AbstractCharacter {
public:
    Hero(string name, int health);

    //vars
    int awareness;
    int baseAttack;
    int baseHealth;
    int baseDefense;

    //functions
    string displayInventory(itemType type);
    string displayInventory();
    string useItem(string itemName);
    string usePotion(string itemName);
    string levelUp(int exp);
    bool move(string direction);

    void addItem(Item* item);
    vector<Item*>* getBag();

    Room* getCurrentRoom();
    void setRoom(Room* room);


private:
    std::vector<Item*> bag;
    Room* currentRoom = nullptr;


};
#endif //ROGUE_HERO_H
