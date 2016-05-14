//
// Created by Mark Jan Kamminga on 14-05-16.
//

#include "RoomVisitor.h"
#include "../ExitRoom.h"

void RoomVisitor::visit(Room *room) {
    output = "N";
}

void RoomVisitor::visit(ExitRoom *room) {
    if (room->isConnectedTo(room->getByEdgeName("down"))) {
        output = "E";
    } else if (room->isConnectedTo(room->getByEdgeName("up"))) {
        output = "U";
    } else {
        output = "T";
    }
}

string RoomVisitor::getOutput() {
    return output;
}
