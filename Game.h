//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_GAME_H
#define ROGUE_GAME_H

//#include <xcmc.h>
#include "Level.h"
#include "Characters/Hero.h"
#include "Items/Item.h"

class Game {
public:
    void setUp(int numLevels, int numXrooms, int numYrooms);
    void itemGenerator();//TODO
    void setCurrentLevel (Level* level);
    Level* getCurrentLevel();
    void load();
    bool save();
    void cleanUpEnemies();
    void cleanUpPotions();
    virtual ~Game();

    vector<Item*>* getItems();
    vector<Enemy*>* getEnemies();
    Hero* getHero();

private:
    Level* currentLevel = nullptr;
    Level** levels = nullptr;
    Hero hero;
    int numLevels;

    vector<Item*> allItems;
    vector<Enemy*> allEnemies;
};

#endif //ROGUE_GAME_H
