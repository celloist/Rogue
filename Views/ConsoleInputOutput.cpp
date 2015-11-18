//
// Created by alhric on 30-Oct-15.
//

#include "ConsoleInputOutput.h"

string ConsoleInputOutput::askInput(string question) {
    cout << question <<endl;
    string input;
    getline(cin,input);
    return input;
}

void ConsoleInputOutput::display(string output) {
    cout << output;
}
