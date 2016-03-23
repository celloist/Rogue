//
// Created by alhric on 10-Nov-15.
//
#include "Item.h"
#include "../Characters/Hero.h"


Item::Item(string name,itemType type,int value) {
    this->name = name;
    this->type = type;
    this->value = value;
}

string Item::getName() {
    return name;
}


itemType Item::getType() {
    return type;
}

int Item::getValue() {
    return value;
}

string Item::use(Hero *hero) {
    return "";
}

bool Item::isUsed() {
    return false;
}

Item::~Item() {

}

bool Item::isAutoUse() {
    return autoUse;
}
