//
// Created by alhric on 30-Oct-15.
//

#include "Game.h"

void Game::setUp(int numLevels, int numXrooms, int numYrooms, LevelDescritions& levelDescritions) {
    levels = new Level*[numLevels];
    this->numLevels = numLevels;

    int numOfEnemiesPerLevel = 0;

    if (enemyPerLevel.size() > 0) {
        if (numLevels < enemyPerLevel.size()) {
            numOfEnemiesPerLevel = (int)floor((enemyPerLevel.size() / numLevels)) ;
        }
    } else {
        throw std::invalid_argument( "empty enemies set" );
    }

    if (allItems.size() == 0) {
        throw std::invalid_argument( "empty items set" );
    }

    if (allTraps.size() == 0) {
        throw std::invalid_argument( "empty traps set" );
    }
    //Copy enemies and items to var
    for (auto it = enemyPerLevel.begin(); it != enemyPerLevel.end(); it++) {
        std::copy(it.operator*().second.begin(), it.operator*().second.end(), back_inserter(allEnemies));
    }

    //randomize items order
    auto toDistItems = allItems;
    auto toDistTraps = allTraps;

    std::random_shuffle(toDistItems.begin(), toDistItems.end());
    std::random_shuffle(toDistTraps.begin(), toDistTraps.end());

    //distribute over the levels
    for(int i = 0; i<numLevels; i++){
        levels[i] = new Level{dre, numXrooms, numYrooms};
        //assign level enemies, dist. items and assign traps
        vector<Enemy*> levelEnemies = distributeEnemiesForLevel(numOfEnemiesPerLevel, i);
        vector<Item*> levelItems    = distributeItemsForLevel(toDistItems);
        vector<Item*> levelTraps    = distributeTrapsForLevel(toDistTraps, i);

        levels[i]->init(levelDescritions, levelEnemies, levelItems, levelTraps);
        if (i > 0) {
            levels[i]->setPrevious(levels[i -1]);
        }

        numInitializedLevels++;
    }

    currentLevel = levels[0];
}

vector<Enemy*> Game::distributeEnemiesForLevel(int numOfEnemiesPerLevel, int level) {
    vector<Enemy*> levelEnemies;

    if (numOfEnemiesPerLevel > 0) {
        int n = level * numOfEnemiesPerLevel;
        int j = n + numOfEnemiesPerLevel;

        if ((level + 1) == numLevels && j < enemyPerLevel.size()) {
            j = enemyPerLevel.size();
        }

        for (; n < j; n++) {
            std::copy(enemyPerLevel[n].begin(), enemyPerLevel[n].end(), back_inserter(levelEnemies));
        }
    } else if ((level + 1) == numLevels) {
        for (auto enemies : enemyPerLevel) {
            std::copy(enemies.second.begin(), enemies.second.end(), back_inserter(levelEnemies));
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

vector<Item *> Game::distributeTrapsForLevel(vector<Trap *>& items, int level) {
    vector<Item *> traps;

    int percentage = (int)(((level +1) / (float)numLevels) * 100);
    if (items.size() > 0) {
        if (percentage == 100) {
            return traps;
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

vector<Item *>* Game::getItems() {
    return &allItems;
}

Hero *Game::getHero() {
    return  &hero;
}
//TODO test
void Game::cleanUpEnemies(vector<Enemy*>* enemies) {
    vector<Enemy* > tmp;
    for(auto it = enemies->begin(); it != enemies->end(); it++) {
        auto enemy = it.operator*();
        if(!enemy->isAlive()){
            auto pos = std::find(allEnemies.begin(), allEnemies.end(), enemy);
            if (pos != allEnemies.end()) {
                allEnemies.erase(pos);
            }

            tmp.push_back(enemy);
        }
    }

    for (auto enemy : tmp) {
        auto pos = std::find(enemies->begin(), enemies->end(), enemy);
        if (pos != enemies->end()) {
            enemies->erase(pos);
            delete enemy;
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

vector<Enemy *> *Game::getEnemies() {
    return &allEnemies;
}

void Game::createEnemiesFromSet(vector<vector<string>> &devidedSetEnemiesDescriptions) {
    for (auto it = devidedSetEnemiesDescriptions.begin(); it != devidedSetEnemiesDescriptions.end(); it++) {
        auto enemiesDescriptionSetRow = it.operator*();
        if (enemiesDescriptionSetRow.size() == 2) {
            //level
            int level = std::atoi(enemiesDescriptionSetRow.at(0).c_str());
            //Get name
            string name = enemiesDescriptionSetRow.at(1);

            Enemy *enemy = new Enemy{name, level, dre};

            if (enemyPerLevel.find(enemy->level) == enemyPerLevel.end()) {
                enemyPerLevel[enemy->level] = vector<Enemy*>{};
            }

            enemyPerLevel[enemy->level].push_back(enemy);
        }
    }
}

vector<Item*> Game::createItemsFromSet(vector<vector<string>> &devidedSetItemsDescriptions) {
    vector<Item*> set;
    for (auto values : devidedSetItemsDescriptions) {
        int type = atoi(values.at(0).c_str());

        string name = values.at(1);
        int value = atoi(values.at(2).c_str());
        Item* item = nullptr;
        if (type == itemType::weapon) {
            item = new Weapon{name, itemType::weapon, value};
        } else if (type == itemType::armor) {
            item = new Armor{name, itemType::armor, value};
        } else if (type == itemType::potion) {
            item = new Potion{name, itemType::potion, value};
        }

        allItems.push_back(item);
        set.push_back(item);
    }

    return set;
}

void Game::createTrapsFromSet(vector<vector<string>> &devidedSetItemsDescriptions) {
    for (auto values : devidedSetItemsDescriptions) {
        int type = atoi(values.at(0).c_str());
        string name = values.at(1);
        int value = atoi(values.at(2).c_str());

        allTraps.push_back(new Trap{name, itemType::trap, value});
    }
}

Game::~Game(){
    for (int i = 0; i<numInitializedLevels; i++) {
        if (levels[i] != nullptr) {
            delete levels[i];
        }
    }

    for(auto item : allEnemies) {
        delete item;
    }

    for (auto item : allItems) {
        delete item;
    }

    for (auto item : allTraps) {
        delete item;
    }
    //delete hero;

    delete[] levels;
}