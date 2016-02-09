//
// Created by alhric on 30-Oct-15.
//

#include "Game.h"
#include "Items/Weapon.h"
#include "Items/Potion.h"

void Game::setUp(int numLevels, int numXrooms, int numYrooms) {

    random_device dev;
    default_random_engine dre {dev()};
    uniform_int_distribution<int> dist {1, 20};

    levels = new Level*[numLevels];
    this->numLevels = numLevels;

    for(int i = 0; i<numLevels; i++){
        levels[i] = new Level{dre};

        levels[i]->init(numXrooms, numYrooms);
        if (i > 0) {
            levels[i]->setPrevious(levels[i -1]);
        }
    }

    currentLevel = levels[0];
}

void Game::setCurrentLevel(Level *level) {
    currentLevel = level;
}

Level* Game::getCurrentLevel() {
    return currentLevel;
}

void Game::load() {}

bool Game::save() {
    return false;
}

Game::~Game(){
    for (int i = 0; i<numLevels; i++) {
        delete levels[i];
    }

    currentLevel = nullptr;
    Hero *hero = nullptr;

    delete currentLevel;
    delete hero;

    delete[] levels;
}

 vector<Item *>* Game::getItems() {
    return &allItems;
}

void Game::itemGenerator() {
    allItems.push_back(new Weapon("Sword", itemType::weapon, 50));
    allItems.push_back(new Potion("HP", itemType::potion, 100));

    for (auto it = allItems.begin(); it != allItems.end(); it++) {
        Item *bagItem = it.operator*();
        hero.addItem(bagItem);
    }


    string item = "sword";
    map<string, itemType> types;
    types["sword"] = itemType::weapon;

    if (types.find(item) != types.end()) {
        auto type = types[item];
        auto bag = hero.getBag();
        for (auto it = bag->begin(); it != bag->end(); it++) {
            Item *bagItem = it.operator*();

            if (bagItem->getType() == type) {
                bagItem->use(&hero);
            }
        }
    }
}


Hero *Game::getHero() {
    return  &hero;
}
