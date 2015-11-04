//
// Created by alhric on 04-Nov-15.
//

#ifndef ROGUE_ROOMPATHNODE_H
#define ROGUE_ROOMPATHNODE_H

#include "Room.h"
 class  RoomPathNode {
 public:
     RoomPathNode(Room* value);
     RoomPathNode* getPrevious();
     RoomPathNode* getNext();

     void setPrevious(RoomPathNode* node);
     void setNext(RoomPathNode* node);
     Room* getValue();

 private:
     RoomPathNode* previous;
     RoomPathNode* next;
     Room* room;

 };
#endif //ROGUE_ROOMPATHNODE_H
