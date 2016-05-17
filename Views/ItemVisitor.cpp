//
// Created by Mark Jan Kamminga on 16-05-16.
//

#include "ItemVisitor.h"

void ItemVisitor::visit(Armor *armor) {
    output = "harnas "+ armor->getName() + " geeft je "+ to_string(armor->getValue());
}

void ItemVisitor::visit(Potion *potion) {
    output = "potion "+ potion->getName() +" geeft je weer "+ to_string(potion->getValue()) +" meer leven.";
}

void ItemVisitor::visit(Weapon *weapon) {
    output = "je hebt "+ to_string(weapon->getValue()) +"meer wapenkracht gekregen door "+ weapon->getName() + ".";
}
