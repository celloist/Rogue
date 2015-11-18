//
// Created by alhric on 05-Nov-15.
//

#include "GameOutput.h"

void GameOutput::displayLevel(Level *currentLevel) {

    Room* current = currentLevel->getNorthEastRoom();
    Room* firstOfTop = current;

    bool hasNextRow = currentLevel->getNorthEastRoom() != nullptr;
    bool hasNextCol = hasNextRow;

    string output;

    while (hasNextRow) {
        while(hasNextCol){
            output+= "*";
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
void GameOutput::displayLevelsMinSpanningTree(Level* currentLevel) {
    Room* current = currentLevel->getNorthEastRoom();
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
                if (currentLevel->isRoomInSPanningTree(current, current->getEast())){
                    top+= "<1>";
                }else {
                    top+= ">0<";
                }
                top+= " ";
            }

            if (current->getSouth() != nullptr) {
                if (currentLevel->isRoomInSPanningTree(current, current->getSouth())){
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
    cout << "\n";
};

void GameOutput::displayLevelsRoomDistances(Level* currentLevel) {
    Room* current = currentLevel->getNorthEastRoom();
    Room* firstOfTop = current;

    bool hasNextRow = currentLevel->getNorthEastRoom() != nullptr;
    bool hasNextCol = hasNextRow;

    string top;
    string bottom;
    while (firstOfTop != nullptr) {
        while(current != nullptr){
            top+=" *";
            if (current->getEast() != nullptr) {
                top+= " <"+ to_string(current->getDistanceTo(current->getEast())) +">";
            }

            if (current->getSouth() != nullptr) {
                bottom += "<"+ to_string(current->getDistanceTo(current->getSouth()))+ ">";

                while (bottom.length() < top.length()) {
                    bottom+=" ";
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
    cout << "\n";
};

void GameOutput::displayShortestPathToExit (map<Room *, pair<int, Room *>> backTrack, Room* start, Room* exit) {
    Room* lastRoom = exit;
    string path;
    int size = backTrack.size();
    int i =0;
    while (lastRoom != start && i < size) {
        auto room = backTrack[lastRoom];
        Room* from = room.second;

        string direction;
        if (lastRoom->getNorth() == from) {
            direction = "zuid";
        } else if (lastRoom->getSouth() == from) {
            direction = "noord";
        }else if (lastRoom->getWest() == from) {
            direction = "oost";
        }else if (lastRoom->getEast() == from) {
            direction = "west";
        }

        if (path.empty()){
            path = direction;
        } else {
            path= direction + " - " + path;
        }

        backTrack.erase(lastRoom);

        lastRoom = from;
        i++;
    }

    cout << "Het kortste pad naar de uitgang is: " + path;
}