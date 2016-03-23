//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ENEMY_H
#define ROGUE_ENEMY_H

#include "iostream"
#include "AbstractCharacter.h"

class Enemy : public AbstractCharacter {
public:
    Enemy (string name, int level,std::default_random_engine &dre) : AbstractCharacter(name, level,dre) {}
    ~Enemy();

};

#endif //ROGUE_ENEMY_H
