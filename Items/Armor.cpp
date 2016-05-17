//
// Created by alhric on 12-Nov-15.
//

#include "Armor.h"
#include "../Characters/Hero.h"

string Armor::use(Hero* hero) {
    hero->defence = (hero->defence) + (this->value);
    return "Je verdedeging is nu " + to_string(hero->defence) +" door harnass: "+ this->name;
}

string Armor::getDescription() {
    return "harnas " + name;
}


void Armor::accept(BaseItemVisitor *visitor) {
    visitor->visit(this);
}
