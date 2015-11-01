//
// Created by alhric on 30-Oct-15.
//

#include "Game.h"

void Game::setUp(int numLevels, int numXrooms, int numYrooms) {
    levels = new Level*[numLevels];
    this->numLevels = numLevels;

    for(int i = 0; i<numLevels; i++){
        levels[i] = new Level;

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
    hero = nullptr;

    delete currentLevel;
    delete hero;

    delete[] levels;
}
