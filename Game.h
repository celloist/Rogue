//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_GAME_H
#define ROGUE_GAME_H

#include "Level.h"
#include "Characters/Hero.h"

class Game {
public:
    void setUp(int numLevels, int numXrooms, int numYrooms);
    void setCurrentLevel (Level* level);
    Level* getCurrentLevel();
    void load();
    bool save();
    void cleanUp();
    virtual ~Game();

private:
    Level* currentLevel = nullptr;
    Level** levels = nullptr;
    Hero* hero = nullptr;
    int numLevels;
};

#endif //ROGUE_GAME_H
