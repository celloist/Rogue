//
// Created by alhric on 30-Oct-15.
//

#include "AbstractCharacter.h"
#include "../Views/ConsoleInputOutput.h"

AbstractCharacter::AbstractCharacter(string name, int health, int level, int attack, int defence, int exp) {

    this->name = name;
    this->health = health;
    this->level = level;
    this->attack = attack;
    this->defence = defence;
    this->exp = exp;
    this->alive = true;
}

AbstractCharacter::AbstractCharacter() {

}

string AbstractCharacter::receiveDamage(int damage) {
    damage = damage - defence;
    if(damage<0)
        damage = 1;

    health = health - damage;
    if(health <1) {
        alive = false;
        return "Dood is alleen maar het begin. "+this->name+" is dood.";
    }

    return name + " heeft "+to_string(damage)+" schade gekregen, "+name+" heeft nog "+to_string(health)+" leven over.";
}
 string AbstractCharacter::attackTarget(AbstractCharacter* target) {
     return target->receiveDamage(attack);
}

bool AbstractCharacter::isAlive() {
    return alive;
}
