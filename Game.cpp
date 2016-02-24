//
// Created by alhric on 30-Oct-15.
//

#include "Game.h"
#include "Items/Weapon.h"
#include "Items/Potion.h"
#include "Characters/Hero.h"

void Game::setUp(int numLevels, int numXrooms, int numYrooms) {
    Hero hero("Kloes",1);
    this->hero = hero;

    random_device dev;
    default_random_engine dre {dev()};

    cout<<"random";
    cout<<dre<<endl;
    uniform_int_distribution<int> dist {1, 20};

    levels = new Level*[numLevels];
    this->numLevels = numLevels;

    for(int i = 0; i<numLevels; i++){
        levels[i] = new Level{dre, numXrooms, numYrooms, this};
        if (i > 0) {
            levels[i]->setPrevious(levels[i -1]);
        }
        levels[i]->init();
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

//TODO generate random objects
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
                cout <<bagItem->use(getHero()) << endl;
            }
        }
    }
}


Hero *Game::getHero() {
    return  &hero;
}
//TODO test
void Game::cleanUp() {
    for(auto it = allEnemies.begin();it!= allEnemies.end();it++)
    {
        Enemy* enemy = it.operator*();
        if(!enemy->isAlive()){
            enemy->~Enemy();
            allEnemies.erase(it);
        }
    }
    allEnemies.clear();
}
