//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ABSTRACTITEM_H
#define ROGUE_ABSTRACTITEM_H

#include "iostream"

using namespace std;

class AbstractItem {
public:
    string getName();

private:
    string name;
};
#endif //ROGUE_ABSTRACTITEM_H
