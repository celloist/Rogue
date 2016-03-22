//
// Created by alhric on 30-Oct-15.
//

#include "Game.h"
#include "Items/Weapon.h"
#include "Items/Potion.h"
#include "Characters/Hero.h"

void Game::setUp(int numLevels, int numXrooms, int numYrooms, LevelDescritions& levelDescritions, map<int, vector<Enemy*>>& enemies) {
    Hero hero("Kloes",1);
    this->hero = hero;



    cout<<"random";
    cout<<dre<<endl;
    uniform_int_distribution<int> dist {1, 20};

    levels = new Level*[numLevels];
    this->numLevels = numLevels;

    int numOfEnemiesPerLevel = 0;

    if (enemies.size() > 0) {
        if (numLevels < enemies.size()) {
            numOfEnemiesPerLevel = enemies.size() / numLevels ;
        }
    } else {
        throw std::invalid_argument( "received empty enemies vector" );
    }

    for(int i = 0; i<numLevels; i++){
        levels[i] = new Level{dre, numXrooms, numYrooms};
        vector<Enemy*> levelEnemies;
        //assign level enemies
        if (numOfEnemiesPerLevel > 0) {
            int n = i * numOfEnemiesPerLevel;
            int j = n + numOfEnemiesPerLevel;

            if ((i + 1) == numLevels && j < enemies.size()) {
                j = enemies.size();
            }

            for (; n < j; n++) {
                std::copy(enemies[n].begin(), enemies[n].end(), back_inserter(levelEnemies));
            }
        } else if ((i + 1) == numLevels) {
            for (auto it = enemies.begin(); it != enemies.end(); it++) {
                std::copy(it.operator*().second.begin(), it.operator*().second.end(), back_inserter(levelEnemies));
            }
        }

        levels[i]->init(levelDescritions, levelEnemies);
        if (i > 0) {
            levels[i]->setPrevious(levels[i -1]);
        }
    }

    for (auto it = enemies.begin(); it != enemies.end(); it++) {
        std::copy(it.operator*().second.begin(), it.operator*().second.end(), back_inserter(allEnemies));
    }

    currentLevel = levels[0];
}

void Game::setCurrentLevel(Level *level) {
    currentLevel = level;
}

Level* Game::getCurrentLevel() {
    if (hero.getCurrentRoom() != nullptr && hero.getCurrentRoom()->getLevel() != currentLevel) {
        setCurrentLevel(hero.getCurrentRoom()->getLevel());
    }
    return currentLevel;
}

Game::~Game(){
    for (int i = 0; i<numLevels; i++) {
        delete levels[i];
    }

    for(auto it = allEnemies.begin();it!= allEnemies.end();it++) {
        delete it.operator*();
    }

    for (auto it = allItems.begin(); it != allItems.end(); it++) {
        delete it.operator*();
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
void Game::cleanUpEnemies() {
    for(auto it = allEnemies.begin();it!= allEnemies.end();it++)
    {
        Enemy* enemy = it.operator*();
        if(!enemy->isAlive()){
            delete enemy;
            allEnemies.erase(it);
        }
    }
    allEnemies.clear();
}


void Game::cleanUpPotions() {
    for(auto it = allItems.begin();it!= allItems.end();it++)
    {
        Item* item = it.operator*();
        if(item->isUsed() ){
            item->~Item();
            allItems.erase(it);
        }
    }
    allItems.clear();

}

void Game::removeItem(Item *item) {
    auto pos = find(allItems.begin(), allItems.end(), item);
    if (pos != allItems.end()){

        delete item;

        allItems.erase(pos);
    }
}

void Game::addItem(Item* item) {
    allItems.push_back(item);
}
