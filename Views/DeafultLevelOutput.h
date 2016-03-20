//
// Created by Mark Jan Kamminga on 17-02-16.
//

#ifndef ROGUE_DEAFULTLEVELOUTPUT_H
#define ROGUE_DEAFULTLEVELOUTPUT_H

#include <string>
#include "GameOutput.h"
#include "../Visitor.h"

using namespace std;

class DeafultLevelOutput : public GameOutput, public Visitor {
public:
    virtual void displayLevel(Level* level);
    void add(string& output);
    void visit(Room*);
    void visit(ExitRoom*);
protected:
    string output;

};


#endif //ROGUE_DEAFULTLEVELOUTPUT_H
