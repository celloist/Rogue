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

                if (current->getByEdgeName("south")){
                    if (current->isConnectedTo(current->getByEdgeName("south"))) {
                        bottom += "|";
                    } else {
                        bottom += "~";
                    }
                }

                if (current->getByEdgeName("east")) {
                    if (current->isConnectedTo(current->getByEdgeName("east"))){
                        output+= "-";
                    } else {
                        output+= "~";
                    }
                    bottom+= " ";
                }

            } else {
                output += ".";
                if (current->getByEdgeName("east")) {
                    output+= " ";
                    bottom+= "  ";
                }
            }


            current = current->getByEdgeName("east");
        }

        cout << output + "\n\n" + bottom + "\n\n";
        output = "";
        bottom = "";

        firstOfTop = firstOfTop->getByEdgeName("south");
        current = firstOfTop;
    }
    cout << "\n";
}

void DeafultLevelOutput::visit(Room *room) {
    output+= "N";
}

void DeafultLevelOutput::visit(ExitRoom *room) {
    if (room->isConnectedTo(room->getByEdgeName("down"))) {
        output += "E";
    } else if (room->isConnectedTo(room->getByEdgeName("up"))) {
        output += "U";
    } else {
        output += "T";
    }
}
