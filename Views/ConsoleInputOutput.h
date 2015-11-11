//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_CONSOLEINPUT_H
#define ROGUE_CONSOLEINPUT_H

#include <iostream>

using namespace std;

class ConsoleInputOutput {
public:
    string askInput(string question);
    void display(string output);
};


#endif //ROGUE_CONSOLEINPUT_H
