//
// Created by alhric on 30-Oct-15.
//

#include <math.h>
#include "AbstractCharacter.h"

AbstractCharacter::AbstractCharacter(string name,int level, default_random_engine& dre) {
    this->name = name;
    this->health = (level* 10);
    this->level = level;
    this->attack = (level *2);
    this->defence = (int) round(level *1.5);
    this->exp = (level * 100);
    this->alive = true;
    this->dre = dre;
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

// random succesfull attack based on attack and defence points rand (a/0.7
// starts out with 50% chance and builds up with the attack. 50+attack and peaks at 95% for chance pick a number between 1 to 100
 string AbstractCharacter::attackTarget(AbstractCharacter* target) {
    int damage = 0;
    int percentage = (attack +50);
    if(percentage> 95)
        percentage = 95;
    //TODO random between 1 and 100 if it falls in the range then attack else return miss
    std::uniform_int_distribution<int> distr(0,100);
    int attackChance = distr(dre);

    if(attackChance<=percentage) {
        //TODO defended damage = random ((defence/4),defence);
        int smallDef = (int)round(defence/8);

        std::uniform_int_distribution<int> attackDis(smallDef,defence);
        int defended = attackDis(dre);
        damage = damage-defended;


    }
    return target->receiveDamage(damage);
}

bool AbstractCharacter::isAlive() {
    return this->alive;
}

