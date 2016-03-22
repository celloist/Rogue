//
// Created by alhric on 30-Oct-15.
//

#include "ExitRoom.h"
#include "Level.h"
#include "Characters/Hero.h"

void ExitRoom::init() {
    if (!initializedLevelEdges) {
        if (level->getNext()) {
            rooms["down"] = make_pair(0, level->getNext()->getExit());
        }

        if (level->getPrevious()) {
            rooms["up"] = make_pair(0,level->getPrevious()->getExit());
        }

        initializedLevelEdges = true;
    }
}

bool ExitRoom::isConnectedTo(Room *edge) {
    if (!initializedLevelEdges){
        init();
    }

    if (rooms["up"].second == edge || rooms["down"].second == edge) {
        return true;
    } else {
        return Room::isConnectedTo(edge);
    }
}

void ExitRoom::moveinHero(Hero *hero){
    if (hero->getCurrentRoom()){
        Room::moveinHero(hero);
    }
    level->setAsCurrentLevel();
}

Room *ExitRoom::getByEdgeName(string name) {
    if (!initializedLevelEdges){
        init();
    }

    return Room::getByEdgeName(name);
}

void ExitRoom::accept(Visitor* v){
    v->visit(this);
}