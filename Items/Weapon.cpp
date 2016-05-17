//
// Created by alhric on 12-Nov-15.
//

#include "Weapon.h"
#include "../Characters/Hero.h"

string Weapon::use(Hero* hero) {
    hero->attack = (hero->baseAttack) + (this->value);
    return "Je doet nu " + to_string(hero->attack) +" meer schade door wapen: "+ this->name +"\n";
}

string Weapon::getDescription() {
    return "wapen "+ name;
}

void Weapon::accept(BaseItemVisitor *visitor) {
    visitor->visit(this);
}
