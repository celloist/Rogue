//
// Created by alhric on 30-Oct-15.
//

#include "ConsoleInputOuput.h"

string ConsoleInputOuput::askInput(string question) {
    cout << question;
    string output;
    cin >> output;

    return output;
}

void ConsoleInputOuput::display(string output) {
    cout << output;
}
