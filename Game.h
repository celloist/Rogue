//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_GAME_H
#define ROGUE_GAME_H

//#include <xcmc.h>
#include "Level.h"
#include "Characters/Hero.h"
#include "Items/Item.h"
#include "Items/Weapon.h"
#include "Items/Trap.h"
#include "Items/Armor.h"
#include "Items/potion.h"

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
    Game(Hero h, default_random_engine &default_rand ) : hero(h), dre(default_rand) {}
    void setUp(int numLevels, int numXrooms, int numYrooms, LevelDescritions& levelDescritions);
    void setCurrentLevel (Level* level);
    Level* getCurrentLevel();
    void cleanUpEnemies(vector<Enemy*>&);
    default_random_engine dre;
    virtual ~Game();
    void addEnemy(Enemy * enemy);
    vector<Item*>* getItems();
    vector<Enemy*>* getEnemies();
    Hero* getHero();
    void removeItem(Item*);
    void addItem(Item*);
    void createEnemiesFromSet(vector<vector<string>>&);
    vector<Item*> createItemsFromSet(vector<vector<string>>&);
    void createTrapsFromSet(vector<vector<string>>&);

private:
    Level* currentLevel = nullptr;
    Level** levels = nullptr;
    Hero hero;
    int numLevels;
    int numInitializedLevels = 0;
    vector<Item*> allItems;
    vector<Enemy*> allEnemies;
    map<int, vector<Enemy*>> enemyPerLevel;
    vector<Trap*> allTraps;

    vector<Enemy*> distributeEnemiesForLevel(int numOfEnemiesPerLevel, int level);
    vector<Item*> distributeItemsForLevel(vector<Item*>&);
    vector<Item*> distributeTrapsForLevel(vector<Trap*>&, int);

};

#endif //ROGUE_GAME_H
