//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ENEMY_H
#define ROGUE_ENEMY_H

#include "iostream"
#include "AbstractCharacter.h"

class Enemy : public AbstractCharacter {
public:
    Enemy (string name, int level) : AbstractCharacter(name, level) {}
    ~Enemy();

};

#endif //ROGUE_ENEMY_H
