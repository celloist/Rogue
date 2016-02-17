//
// Created by Mark Jan Kamminga on 17-02-16.
//

#include "DeafultLevelOutput.h"

void DeafultLevelOutput::add(string &output) {
    this->output+= output;
}

void DeafultLevelOutput::displayLevel(Level *currentLevel) {
    Room* current = currentLevel->getNorthEastRoom();
    Room* firstOfTop = current;

    bool hasNextRow = currentLevel->getNorthEastRoom() != nullptr;
    bool hasNextCol = hasNextRow;

    while (hasNextRow) {
        while(hasNextCol){
            if (current->hasBeenVisited()) {
                current->accept(this);
            } else {
                output += "*";
            }
            if (current->getEast() != nullptr) {
                current = current->getEast();
            } else {
                hasNextCol = false;
            }
        }

        cout << output + "\n";
        output = "";

        if (firstOfTop->getSouth() != nullptr) {
            firstOfTop = firstOfTop->getSouth();
            current = firstOfTop;
            hasNextCol = true;
        } else {
            hasNextRow = false;
        }
    }

    cout << "\n";
}

void DeafultLevelOutput::visit(Room *room) {
    output+= "N";
}


void DeafultLevelOutput::visit(ExitRoom *room) {
    output+= "T";
}
