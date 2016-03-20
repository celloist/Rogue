//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ABSTRACTCHARACTER_H
#define ROGUE_ABSTRACTCHARACTER_H

#include "iostream"
using namespace std;

class AbstractCharacter {
public:
    AbstractCharacter();
    AbstractCharacter(string name,int level);

    //vars are public because they need to be manipulated


    //functions
    virtual string attackTarget(AbstractCharacter* target);

    bool isAlive();

    string name;
    int health;
    int level;
    int attack;
    int defence;
    int exp;
    bool alive;

protected:
    virtual string receiveDamage(int damage);

};
#endif //ROGUE_ABSTRACTCHARACTER_H
