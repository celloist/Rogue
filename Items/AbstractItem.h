//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_ABSTRACTITEM_H
#define ROGUE_ABSTRACTITEM_H

#include "iostream"

using namespace std;

enum itemType{
    normal,
    potion
};


 class AbstractItem {
public:
     AbstractItem();
     AbstractItem(string name);
     string getName();
    itemType getType();
    virtual string use();
     ~AbstractItem();

 protected:
     string name;
     itemType type;
 };
#endif //ROGUE_ABSTRACTITEM_H
