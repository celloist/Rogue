//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_HERO_H
#define ROGUE_HERO_H

#include <vector>
#include "AbstractCharacter.h"
#include "iostream"
#include "../Items/Item.h"

using namespace std;

class Hero : AbstractCharacter {
public:
    Hero(string name);

    //vars
    int awareness;

    //functions
    std::vector<AbstractItem*> getBag();
    void addItem(Item item);
    void useItem(string itemName);
    void levelUp();

private:
    std::vector<Item> bag;
};
#endif //ROGUE_HERO_H
