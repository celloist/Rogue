//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_HERO_H
#define ROGUE_HERO_H

#include <vector>
#include "AbstractCharacter.h"
#include "iostream"

class Item;

using namespace std;

class Hero : AbstractCharacter {
public:
    Hero();
    Hero(string name);

    //vars
    int awareness;

    //functions
    void useItem(string itemName);
    void levelUp();

    void addItem(Item* item);
    vector<Item*>* getBag();

private:
    std::vector<Item*> bag;
};
#endif //ROGUE_HERO_H
