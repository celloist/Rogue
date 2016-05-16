//
// Created by Mark Jan Kamminga on 28-02-16.
//

#include "Trap.h"
#include "../Characters/Hero.h"

string Trap::use(Hero *hero) {
    if (hero->awareness >= value) {
        hero->alive = false;

        return "hero died in trap: "+ this->name;
    }
    return "trap found: "+ this->name;
}

string Trap::getDescription() {
    return "val "+ name;
}
