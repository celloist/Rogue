//
// Created by alhric on 30-Oct-15.
//
#include <math.h>
#include "Hero.h"

Hero::Hero(string name, int level) {
    this->name = name;
    this->baseHealth= (level*11);
    this->level = level;
    this->baseAttack = (level*3);
    this->baseDefense = (level*2);
    this->exp = 0;
    this->alive = true;
    this->awareness = (int) round(level * 1.4);
}

void Hero::addItem(Item *item) {
    bag.push_back(item);
}

vector<Item *>* Hero::getBag() {
    return &bag;
}

Room *Hero::getCurrentRoom() {
    return currentRoom;
}

//Displays potion or a combination of weapons and armor
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

//displays all items
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

string Hero::levelUp(int exp) {
    if(exp ==0)
        return "";

        this->exp += exp;
        int oldLevel = level;
        level = (this->exp / 400);
        string message = "Je hebt " + exp;
        message = message + " erbij verdient. \n";
        if (level > oldLevel) {
            message = "Je hebt een nieuwe level erbij gekregen! Je bent nu level:" + level;
            message = message + ". \n";
        }
        return message;

}

void Hero::clearItems() {
    bag.clear();
}
