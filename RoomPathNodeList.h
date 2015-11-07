//
// Created by Mark Jan Kamminga on 05-11-15.
//

#ifndef ROGUE_ROOMPATHNODELIST_H
#define ROGUE_ROOMPATHNODELIST_H


#include "RoomPathNode.h"

class RoomPathNodeList {
    void insert(Room* room, int distance);
    RoomPathNode* first();
    RoomPathNode* last();
};


#endif //ROGUE_ROOMPATHNODELIST_H
