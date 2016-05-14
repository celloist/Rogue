//
// Created by Mark Jan Kamminga on 14-05-16.
//

#include "utils.h"

vector<string> readFile (std::string textfile) {
    ifstream input_file{textfile};

    if (!input_file.is_open()) {
        throw std::runtime_error("Could not open file: "+ textfile);
    }
    string line;
    vector<string> list;

    while (getline(input_file, line)) {
        list.push_back(line);
    }

    input_file.close();

    return list;
}

vector<string> devideString (const string& input, char divider) {
    vector<string> divided;

    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, divider)) {
        divided.push_back(item);
    }

    return divided;
};

vector<vector<string>> devideSet (const vector<string>& set, char divider) {
    vector<vector<string>> devidedSet;

    for (auto it = set.begin(); it != set.end(); it++) {
        devidedSet.push_back(devideString(it.operator*(), divider));
    }

    return devidedSet;
}