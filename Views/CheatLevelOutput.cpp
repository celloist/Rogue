//
// Created by Mark Jan Kamminga on 09-03-16.
//

#include "CheatLevelOutput.h"

void CheatLevelOutput::displayLevel(Level *currentLevel) {
    Room* current = currentLevel->getNorthEastRoom();
    Room* firstOfTop = current;

    bool hasNextRow = currentLevel->getNorthEastRoom() != nullptr;
    bool hasNextCol = hasNextRow;

    string bottom;
    string trapsAndEnemies= "";
    int index = 1;
    while (firstOfTop != nullptr) {
        char letter = 'A';
        while(current != nullptr){

            current->accept(this);
            //output = output + " ";

            string num;

            if (current->getByEdgeName("east") != nullptr) {
                if (current->isConnectedTo(current->getByEdgeName("east"))) {
                    num = to_string(current->getDistanceTo(current->getByEdgeName("east")));
                    output+= " <"+ ((num.length() <= 1) ? " " + num : num ) +">";
                } else {
                    output += " < ~>";
                }

                output+= " ";
            }

            if (current->getByEdgeName("south") != nullptr) {
                if (current->isConnectedTo(current->getByEdgeName("south"))) {
                    num = to_string(current->getDistanceTo(current->getByEdgeName("south")));
                    bottom += "<" + ((num.length() <= 1) ? " " + num : num) + "> ";
                } else {
                    bottom += "< ~> ";
                }


                while (bottom.length() < output.length() -1) {
                    bottom+=" ";
                }
            }

            if (current->getEnemies() && current->getEnemies()->size() > 0 || current->hasTrap()) {
                trapsAndEnemies+=  letter + to_string(index) + ": \n";
                if (current->hasTrap()) {
                    trapsAndEnemies+= "- Heeft een val!\n";
                }

                if (current->getEnemies() && current->getEnemies()->size() > 0) {
                    vector<Enemy*>* enemies = current->getEnemies();

                    string hp = "";
                    for (auto it = enemies->begin(); it != enemies->end(); it++) {
                        if (hp.length() == 0) {
                            hp+= to_string(it.operator*()->health);
                        } else {
                            hp+= ", "+ to_string(it.operator*()->health);
                        }
                    }

                    trapsAndEnemies+= "Heeft "+ to_string(enemies->size()) + " vijand(en) met ("+ hp + ")\n";
                }

                trapsAndEnemies+= "\n";
            }

            current = current->getByEdgeName("east");
            letter++;
        }

        cout << output + "\n\n" + bottom + "\n\n";
        output = "";
        bottom = "";

        firstOfTop = firstOfTop->getByEdgeName("south");
        current = firstOfTop;
        index++;
    }

    cout << trapsAndEnemies;
    cout << "\n";
}
