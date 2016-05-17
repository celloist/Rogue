//
// Created by Mark Jan Kamminga on 17-05-16.
//

#include "ItemDescriptorVisitor.h"
#include "../Items/Armor.h"
#include "../Items/Weapon.h"
#include "../Items/potion.h"
#include "../Items/Trap.h"

void ItemDescriptorVisitor::visit(Armor *armor) {
    output = "harnass met naam "+ armor->getName();
}

void ItemDescriptorVisitor::visit(Potion *potion) {
    output = "speciale drankje die gaat onder de naam van: "+ potion->getName();
}

void ItemDescriptorVisitor::visit(Weapon *weapon) {
    output = "Speciale wapen met de geweldige naam van: "+ weapon->getName();
}

void ItemDescriptorVisitor::visit(Trap *trap) {

}
