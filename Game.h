//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_GAME_H
#define ROGUE_GAME_H

//#include <xcmc.h>
#include "Level.h"
#include "Characters/Hero.h"
#include "Items/Item.h"

struct LevelDescritions {
public:
    vector<string> decorations;
    vector<string> furniture;
    vector<string> lightsources;
    vector<string> sizes;
    vector<string> sounds;
    vector<string> tidyness;
    vector<string> misc;

    LevelDescritions(vector<string> dec,
                     vector<string> fur,
                     vector<string> light,
                     vector<string> sizes,
                     vector<string> sounds,
                     vector<string> tidyness,
                     vector<string> misc){

        decorations = dec;
        furniture = fur;
        lightsources = light;
        this->sizes = sizes;
        this->sounds = sounds;
        this->tidyness = tidyness;
        this->misc = misc;
    }
};

class Game {
public:
    Game() : hero(Hero("Kloes",500,1,20,40,0,true,1)) {}
    void setUp(int numLevels, int numXrooms, int numYrooms, LevelDescritions& levelDescritions);
    void itemGenerator();//TODO
    void setCurrentLevel (Level* level);
    Level* getCurrentLevel();
    void cleanUp();
    void createEnemiesForLevel(int level);
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
