//
// Created by alhric on 04-Nov-15.
//

#include "RoomPathNode.h"

RoomPathNode::RoomPathNode (Room* value) {
    room = value;
}

RoomPathNode* RoomPathNode::getPrevious(){
    return previous;
}

RoomPathNode* RoomPathNode::getNext() {
    return next;
}

void RoomPathNode::setPrevious(RoomPathNode *room) {
    previous = room;
}

void RoomPathNode::setNext(RoomPathNode *room) {
    next = room;
}

Room* RoomPathNode::getValue() {
    return room;
}
