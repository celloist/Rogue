//
// Created by alhric on 30-Oct-15.
//

#include "Game.h"

void Game::setUp(int numLevels, int numXrooms, int numYrooms, LevelDescritions& levelDescritions, map<int, vector<Enemy*>>& enemies, vector<Item*>& items, vector<Item*>& traps) {
    uniform_int_distribution<int> dist {1, 20};

    levels = new Level*[numLevels];
    this->numLevels = numLevels;

    int numOfEnemiesPerLevel = 0;

    if (enemies.size() > 0) {
        if (numLevels < enemies.size()) {
            numOfEnemiesPerLevel = (int)floor((enemies.size() / numLevels)) ;
        }
    } else {
        throw std::invalid_argument( "received empty enemies vector" );
    }
    //Copy enemies and items to var
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
        std::copy(it.operator*().second.begin(), it.operator*().second.end(), back_inserter(allEnemies));
    }

    std::copy(items.begin(), items.end(), back_inserter(allItems));
    //randomize items order
    std::random_shuffle(items.begin(), items.end());
    std::random_shuffle(traps.begin(), traps.end());

    //distribute over the levels
    for(int i = 0; i<numLevels; i++){
        levels[i] = new Level{dre, numXrooms, numYrooms};
        //assign level enemies, dist. items and assign traps
        vector<Enemy*> levelEnemies = distributeEnemiesForLevel(numOfEnemiesPerLevel, i, enemies);
        vector<Item*> levelItems    = distributeItemsForLevel(items);
        vector<Item*> levelTraps    = distributeTrapsForLevel(traps, i);

        levels[i]->init(levelDescritions, levelEnemies, levelItems, levelTraps);
        if (i > 0) {
            levels[i]->setPrevious(levels[i -1]);
        }
    }

    currentLevel = levels[0];
}

vector<Enemy*> Game::distributeEnemiesForLevel(int numOfEnemiesPerLevel, int level, map<int, vector<Enemy*>>& enemies) {
    vector<Enemy*> levelEnemies;

    if (numOfEnemiesPerLevel > 0) {
        int n = level * numOfEnemiesPerLevel;
        int j = n + numOfEnemiesPerLevel;

        if ((level + 1) == numLevels && j < enemies.size()) {
            j = enemies.size();
        }

        for (; n < j; n++) {
            std::copy(enemies[n].begin(), enemies[n].end(), back_inserter(levelEnemies));
        }
    } else if ((level + 1) == numLevels) {
        for (auto it = enemies.begin(); it != enemies.end(); it++) {
            std::copy(it.operator*().second.begin(), it.operator*().second.end(), back_inserter(levelEnemies));
        }
    }

    return levelEnemies;
}

vector<Item*> Game::distributeItemsForLevel(vector<Item*>& items){
    vector<Item*> levelItems;
    int numItems = (int)floor(items.size() / 2);
    if (numItems > 0) {
        std::copy(items.begin(), items.begin() + numItems, back_inserter(levelItems));
        items.erase(items.begin(), items.begin() + numItems);
    } else {
        return items;
    }

    return levelItems;
}

vector<Item *> Game::distributeTrapsForLevel(vector<Item *>& items, int level) {
    vector<Item *> traps;

    int percentage = (int)(((level +1) / (float)numLevels) * 100);
    if (items.size() > 0) {
        if (percentage == 100) {
            return items;
        }
        float subRange = ((items.size() - 1) / 100.00);
        int maxRange = (int)ceil(subRange * percentage);
        uniform_int_distribution<int> dist{0, maxRange};

        int range = dist(dre);

        if (range > 0) {
            std::copy(items.begin(), items.begin() + range, back_inserter(traps));
            items.erase(items.begin(), items.begin() + range);
        }
    }

    return traps;
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
}


void Game::cleanUpPotions() {
    for(auto it = allItems.begin();it!= allItems.end();it++)
    {
        Item* item = it.operator*();
        if(item->isUsed() ){
            delete item;
            allItems.erase(it);
        }
    }

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

void Game::addEnemy(Enemy *enemy) {
    allEnemies.push_back(enemy);
}


vector<Enemy *> Game::getEnemies() {
    return allEnemies;
}
