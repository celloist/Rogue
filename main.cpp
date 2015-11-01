#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    Game game;

    game.setUp(3, 10, 10);

    Level* currentLevel = game.getCurrentLevel();

    Room* firstOfTop = currentLevel->getNorthEastRoom();
    Room* current = firstOfTop;

    bool hasNextRow = currentLevel->getNorthEastRoom() != nullptr;
    bool hasNextCol = hasNextRow;

    while (hasNextRow) {
        while(hasNextCol){
            cout << "*";
            if (current->getEast() != nullptr) {
                current = current->getEast();
            } else {
                hasNextCol = false;
            }
        }

        cout << "\n";

        if (firstOfTop->getSouth() != nullptr) {
            firstOfTop = firstOfTop->getSouth();
            current = firstOfTop;
            hasNextCol = true;
        } else {
            hasNextRow = false;
        }
    }

    return 0;
}