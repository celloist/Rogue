//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ABSTRACTCHARACTER_H
#define ROGUE_ABSTRACTCHARACTER_H

#include "iostream"
using namespace std;

class AbstractCharacter {

public:
    //vars are public because they need to be manipulated
    string name;
    int health;
    int level;
    int attack;
    int defence;
    int exp;

    //functions
    string attackTarget(int &targethealth,int &targetattack,int &targetdefence);



private:

};
#endif //ROGUE_ABSTRACTCHARACTER_H
