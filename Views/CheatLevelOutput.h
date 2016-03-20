//
// Created by Mark Jan Kamminga on 09-03-16.
//

#ifndef ROGUE_CHEATLEVELOUTPUT_H
#define ROGUE_CHEATLEVELOUTPUT_H


#include "DeafultLevelOutput.h"

class CheatLevelOutput : public DeafultLevelOutput{
public:
    virtual void displayLevel(Level*);
};


#endif //ROGUE_CHEATLEVELOUTPUT_H
