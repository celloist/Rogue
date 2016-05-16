//
// Created by Mark Jan Kamminga on 14-05-16.
//

#ifndef ROGUE_UTILS_H
#define ROGUE_UTILS_H


//
// Created by Mark Jan Kamminga on 14-05-16.
//
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> readFile (std::string textfile);

vector<string> devideString (const string& input, char divider);

vector<vector<string>> devideSet (const vector<string>& set, char divider);


#endif //ROGUE_UTILS_H
