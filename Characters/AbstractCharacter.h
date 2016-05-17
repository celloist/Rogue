//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ABSTRACTCHARACTER_H
#define ROGUE_ABSTRACTCHARACTER_H

#include <algorithm>
#include <random>
#include "iostream"

using namespace std;

class AbstractCharacter {
public:
    AbstractCharacter(){}
    AbstractCharacter(string name,int level, default_random_engine& dre);

    //vars are public because they need to be manipulated


    //functions
    virtual int attackTarget(AbstractCharacter* target);

    bool isAlive();

    string name;
    int health = 100;
    int level;
    int attack;
    int defence;
    int exp;
    bool alive;
    default_random_engine dre;

protected:
    virtual int receiveDamage(int damage);

};
#endif //ROGUE_ABSTRACTCHARACTER_H
