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


    string bottom;
    while (firstOfTop != nullptr) {
        while(current != nullptr){
            if (current->hasBeenVisited()) {
                current->accept(this);

                if (current->getSouth()){
                    if (current->isConnectedTo(current->getSouth())) {
                        bottom += "|";
                    } else {
                        bottom += "~";
                    }
                }

                if (current->getEast()) {
                    if (current->isConnectedTo(current->getEast())){
                        output+= "-";
                    } else {
                        output+= "~";
                    }
                    bottom+= " ";
                }

            } else {
                output += ".";
                if (current->getEast()) {
                    output+= " ";
                    bottom+= "  ";
                }
            }


            current = current->getEast();
        }

        cout << output + "\n\n" + bottom + "\n\n";
        output = "";
        bottom = "";

        firstOfTop = firstOfTop->getSouth();
        current = firstOfTop;
    }
    cout << "\n";
}

void DeafultLevelOutput::visit(Room *room) {
    output+= "N";
}


void DeafultLevelOutput::visit(ExitRoom *room) {
    output+= "T";
}
