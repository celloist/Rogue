//
// Created by alhric on 12-Nov-15.
//

#include "Armor.h"
#include "../Characters/Hero.h"

string Armor::use(Hero* hero) {
    hero->defence = (hero->baseDefense) + (this->value);
    return "Je verdedeging is nu " + to_string(hero->defence) +" door harnass: "+ this->name;
}
