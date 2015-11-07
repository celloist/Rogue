//
// Created by alhric on 05-Nov-15.
//

#ifndef ROGUE_GAMEOUTPUT_H
#define ROGUE_GAMEOUTPUT_H


#include "../Level.h"

class GameOutput{
public:
    void displayLevel(Level* level);
    void displayLevelsMinSpanningTree(Level* currentLevel);
    void displayLevelsRoomDistances(Level* currentLevel);
};

#endif //ROGUE_GAMEOUTPUT_H
