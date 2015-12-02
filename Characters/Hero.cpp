//
// Created by alhric on 30-Oct-15.
//
#include "Hero.h"

void Hero::addItem(Item *item) {
    bag.push_back(item);
}

vector<Item *>* Hero::getBag() {
    return &bag;
}


Hero::Hero(string name) {
 this->name = name;
}

Hero::Hero(string name, int health, int level, int attack, int defence, int exp, bool alive, int awareness) {
    this->name = name;
    this->baseHealth= health;
    this->level = level;
    this->baseAttack = attack;
    this->baseDefense = defence;
    this->exp = exp;
    this->alive = alive;
    this->awareness = awareness;
}

Hero::Hero() {
    this->name = "test";
}

Room *Hero::getCurrentRoom() {
    return currentRoom;
}

bool Hero::useItem(string itemName,ConsoleInputOutput* io) {

    string useInfo = "";
    for ( auto it = bag.begin(); it!= bag.end(); ++it)
    {
        auto item = it.operator*();
        if(item->getName() == itemName)
        {
            if(item->getType() != itemType::potion){
                useInfo = item->use(this);
                io->display(useInfo);
                return true;
            }
        }
    }
    return false;
}

bool Hero::usePotion(string itemName, ConsoleInputOutput *io) {
    string useInfo = "";
    for ( auto it = bag.begin(); it!= bag.end(); ++it)
    {
        auto item = it.operator*();
        if(item->getName() == itemName)
        {
            if(item->getType() == itemType::potion){
                io->display(useInfo);
                delete *it;
                bag.erase(it);
                return true;
            }
        }
    }
    return false;
}

