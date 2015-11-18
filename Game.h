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
    //void setHero(Hero hero);
    void itemGenerator();//TODO
    void setCurrentLevel (Level* level);
    Level* getCurrentLevel();
    void load();
    bool save();
    void cleanUp();
    virtual ~Game();

    vector<Item*>* getItems();
    Hero* getHero();

private:
    Level* currentLevel = nullptr;
    Level** levels = nullptr;
    Hero hero;
    int numLevels;

    vector<Item*> allItems;
};

#endif //ROGUE_GAME_H
