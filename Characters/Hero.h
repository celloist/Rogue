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
    Hero();
    Hero(string name);
    Hero(string name,int health,int level,int attack,int defence,int exp, bool alive, int awareness);

    //vars
    int awareness;
    int baseAttack;
    int baseHealth;
    int baseDefense;

    //functions
    bool useItem(string itemName,ConsoleInputOutput* io);
    bool usePotion(string itemName,ConsoleInputOutput* io);
    void levelUp();
    bool move(string direction);

    void addItem(Item* item);
    vector<Item*>* getBag();

    Room* getCurrentRoom();



private:
    std::vector<Item*> bag;
    Room* currentRoom;
};
#endif //ROGUE_HERO_H
