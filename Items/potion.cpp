//
// Created by alhric on 12-Nov-15.
//

#include "Potion.h"
#include "../Characters/Hero.h"

string Potion::use(Hero* hero) {
    if(used)
        return this->name+" all gebruikt";

    if(((hero->health)+this->value)> (hero->baseHealth) ) {
        hero->health = (hero->baseHealth);
    }
    else {
        hero->health = (hero->health) + (this->value);
    }
    used = true;
    return "Je heb je zelf genezen, je hp is nu " + to_string(hero->health) +" door drankje: "+ this->name;
}

bool Potion::isUsed() {
    return used;
}
