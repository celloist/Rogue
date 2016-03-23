//
// Created by alhric on 05-Nov-15.
//

#include "GameOutput.h"

void GameOutput::displayLevel(Level *currentLevel) {
    /*
    Room* current = currentLevel->getNorthEastRoom();
    Room* firstOfTop = current;

    bool hasNextRow = currentLevel->getNorthEastRoom() != nullptr;
    bool hasNextCol = hasNextRow;

    string output;

    while (hasNextRow) {
        while(hasNextCol){
            if (current->hasBeenVisited()) {
                output += "n";
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

    cout << "\n";*/
}
void GameOutput::displayLevelsMinSpanningTree(Level* currentLevel) {
    /*Room* current = currentLevel->getNorthEastRoom();
    Room* firstOfTop = current;

    bool hasNextRow = currentLevel->getNorthEastRoom() != nullptr;
    bool hasNextCol = hasNextRow;

    string top;
    string bottom;
    //bottom+=  " ["+ to_string(current->getDistanceTo(current->getEast())) +"] " ;
    while (firstOfTop != nullptr) {
        while(current != nullptr){
            top+= " *";
            if (current->getEast() != nullptr) {
                top+= " ";
                if (currentLevel->isRoomInSpanningTree(current, current->getEast())){
                    top+= "<1>";
                }else {
                    top+= ">0<";
                }
                top+= " ";
            }

            if (current->getSouth() != nullptr) {
                if (currentLevel->isRoomInSpanningTree(current, current->getSouth())){
                    bottom+= "<1>";
                }else {
                    bottom+= ">0<";
                }

                if (current->getEast() != nullptr) {
                    bottom += "    ";
                }
            }

            current = current->getEast();
        }

        cout << top + "\n" + bottom + "\n";
        top = "";
        bottom = "";

        firstOfTop = firstOfTop->getSouth();
        current = firstOfTop;
    }
    cout << "\n";*/
};

void GameOutput::displayShortestPathToExit (map<Room *, pair<int, Room *>> backTrack, Room* start, Room* exit) {
    Room* lastRoom = exit;
    string path;
    int size = backTrack.size();
    int i =0;
    int numOfEnemies = 0;
    string hp;
    int numOfTraps = 0;

    while (lastRoom != start && i < size) {
        auto room = backTrack[lastRoom];
        Room* from = room.second;

        string direction;
        /*
         * guage direction
         */
        if (lastRoom->getByEdgeName("north") == from) {
            direction = "zuid";
        } else if (lastRoom->getByEdgeName("south") == from) {
            direction = "noord";
        }else if (lastRoom->getByEdgeName("west") == from) {
            direction = "oost";
        }else if (lastRoom->getByEdgeName("east") == from) {
            direction = "west";
        }

        if (path.empty()){
            path = direction;
        } else {
            path= direction + " - " + path;
        }

        /*
         * Add enemies
         */

        if (from->getEnemies()) {
            vector<Enemy*>* enemies = from->getEnemies();
            for (auto it = enemies->begin(); it != enemies->end(); it++) {
                numOfEnemies++;

                if (hp.length() > 1) {
                    hp += ", " + to_string(it.operator*()->health);
                } else {
                    hp += to_string(it.operator*()->health);
                }

                hp+= " hp";
            }
        }

        if (from->hasTrap()) {
            numOfTraps++;
        }

        backTrack.erase(lastRoom);

        lastRoom = from;
        i++;
    }

    string output = "Het kortste pad naar de uitgang is: " + (path.size() > 0 ? path : "hier blijven")  + ".\n";

    if (numOfEnemies > 0) {
        output+= "Aantal vijanden: "+ to_string(numOfEnemies) + " (" + hp + ").";
    } else {
        output+= "Geen vijanden.";
    }

    output+= "\n";

    if (numOfTraps > 0) {
        output+= "Aantal vallen: "+ to_string(numOfTraps);
    } else {
        output+= "Geen vallen.";
    }

    cout << output + "\n";
}