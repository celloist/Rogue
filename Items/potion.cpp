//
// Created by alhric on 12-Nov-15.
//

#include "Potion.h"
#include "../Characters/Hero.h"

string Potion::use(Hero* hero) {
    hero->health = (hero->health) + (this->value);
    if (hero->health > 100) {
        hero->health = 100;
    }

    used = true;

    return "Je heb je zelf genezen, je hp is nu " + to_string(hero->health) +" door drankje: "+ this->name +"\n";
}

bool Potion::isUsed() {
    return used;
}

string Potion::getDescription() {
    return "drankje " + name;
}

Potion::~Potion() {

}

void Potion::accept(BaseItemVisitor *visitor) {
    visitor->visit(this);
}
