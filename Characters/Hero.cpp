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

//There are 3 options here you can get potions, other items or all items by giving a NULL value as itemType
string Hero::displayInventory(itemType type) {
    string items = "";
    for (auto it = bag.begin(); it != bag.end(); it++) {
        if (type == itemType::potion) {
            if (it.operator*()->getType() == type) {
                items += it.operator*()->getName() + " ,";
            }
        }
        else{
            if (it.operator*()->getType() != itemType::potion) {
                items += it.operator*()->getName() + " ,";
            }
        }
    }
}

string Hero::displayInventory() {
    string items = "";
    for (auto it = bag.begin(); it != bag.end(); it++) {
                items += it.operator*()->getName() + " ,";
    }
    return items;
}

string Hero::useItem(string itemName) {

    string useInfo = "";
    for ( auto it = bag.begin(); it!= bag.end(); ++it)
    {
        auto item = it.operator*();
        if(item->getName() == itemName && item->getType() != itemType::potion)
        {
            useInfo = item->use(this);
            return useInfo;
        }
    }
    return "Object niet gevonden probeer de bekijk spullen commando \n";
}




string Hero::usePotion(string itemName) {


    string useInfo = "";
    for ( auto it = bag.begin(); it!= bag.end(); ++it)
    {
        auto* item = it.operator*();
        if(item->getName() == itemName)
        {
            if(item->getType() == itemType::potion){
                useInfo = item->use(this);
                bag.erase(it);
                bag.clear();
                return useInfo;
            }
        }
    }
    return "Drankje niet gevonden probeer de bekijk spullen commando \n";
}


void Hero::setRoom(Room *room) {
    if (currentRoom) {
        currentRoom->moveoutHero();
    }
    room->moveinHero(this);
    this->currentRoom = room;
}
