//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_GAME_H
#define ROGUE_GAME_H

#include "Level.h"
#include "Characters/Hero.h"

class Game {
public:
    void setCurrentLevel (Level* level);
    Level* getCurrentLevel();
    void load();
    bool save();
private:
    Level* currentLevel;
    Hero* hero;

};

#endif //ROGUE_GAME_H
