//
// Created by alhric on 30-Oct-15.
//

#include "ExitRoom.h"
#include "Level.h"
#include "Characters/Hero.h"

bool ExitRoom::isConnectedTo(Room *edge) {

    if (edge && (rooms["up"].second == edge || rooms["down"].second == edge)) {
        return true;
    } else {
        return Room::isConnectedTo(edge);
    }
}

void ExitRoom::setEdge(string name, Room* edge, int distance) {
    if (name == "up" || name == "down") {
        rooms[name] = make_pair(0, edge);
    } else {
        Room::setEdge(name, edge, distance);
    }
};

void ExitRoom::accept(Visitor* v){
    v->visit(this);
}
