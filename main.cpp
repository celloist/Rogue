#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    Game game;

    game.setUp(1, 2, 2);

    Level* currentLevel = game.getCurrentLevel();

    Room* firstOfTop = currentLevel->getNorthEastRoom();
    Room* current = firstOfTop;
    int num = current->findExitRoom();

    bool hasNextRow = currentLevel->getNorthEastRoom() != nullptr;
    bool hasNextCol = hasNextRow;
    string top;
    string bottom;
    while (hasNextRow) {
        bottom+= " ";
        while(hasNextCol){

            if (current->getNorth() != nullptr){
                top+= "["+ to_string(current->getDistanceTo(current->getNorth())) +"] " + (currentLevel->isRoomInSPanningTree(current, current->getNorth() ) ? "1" : "0" ) + " ";
            }

            bottom+= "*";
            if (current->getEast() != nullptr) {
                bottom+=  " ["+ to_string(current->getDistanceTo(current->getEast())) +"] " + (currentLevel->isRoomInSPanningTree(current, current->getEast() ) ? "1" : "0" ) + " ";

                int appendSize = bottom.size() - top.size();
                int i = 0;
                while (appendSize != bottom.size() && i < (appendSize -1)) {
                    top+= " ";
                    i++;
                }

                current = current->getEast();
            } else {
                hasNextCol = false;
            }
        }

        cout << top << (top.size() > 0 ? "\n" : "") << bottom << "\n";
        bottom = "";
        top = "";

        if (firstOfTop->getSouth() != nullptr) {
            firstOfTop = firstOfTop->getSouth();
            current = firstOfTop;
            hasNextCol = true;
        } else {
            hasNextRow = false;
        }
    }

    cout << "Num of steps from start[west] [left top], til bottom: right under: "+ to_string(num);

    return 0;
}