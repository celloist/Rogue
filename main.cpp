#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    Game game;

    game.setUp(1, 400, 400);

    Level* currentLevel = game.getCurrentLevel();

    Room* firstOfTop = currentLevel->getNorthEastRoom();
    Room* current = firstOfTop;
    int num = current->findExitRoom();
    cout << num;
    return 0;
}