//
// Created by alhric on 30-Oct-15.
//

#include <math.h>
#include <random>
#include "AbstractCharacter.h"

AbstractCharacter::AbstractCharacter(string name,int level, default_random_engine& dre) {
    this->name = name;
    this->level = level;
    this->attack = (level *20);
    this->defence = (level * 10);
    this->exp = (level * 100);
    this->alive = true;
}

int AbstractCharacter::receiveDamage(int damage) {
    int damageReceived = damage - defence;

    if (damageReceived < 0) {
        damageReceived = 0;
    }

    health = health - damage;
    if(health <= 0) {
        alive = false;
    }

    return damageReceived;
}

int AbstractCharacter::attackTarget(AbstractCharacter* target) {
    int damage = 0;

    uniform_int_distribution<int> dist {1, 5};

    int hitChance = dist(dre);

    if (hitChance > 1) {

        int from = (attack > 0) ? attack  / 2 : 0;
        uniform_int_distribution<int> damageDist {from, attack};

        damage = damageDist(dre);
    }

    return target->receiveDamage(damage);
}

bool AbstractCharacter::isAlive() {
    return alive;
}

