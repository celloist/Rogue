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

}

Hero::Hero() {
    this->name = "test";
}
