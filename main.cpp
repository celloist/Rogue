#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    Game game;

    game.setUp(1, 4000, 4000);

    Level* currentLevel = game.getCurrentLevel();

    Room* firstOfTop = currentLevel->getNorthEastRoom();
    Room* current = firstOfTop;
    //int num = current->getSouth()->getSouth()->findExitRoom();

    return 0;
}