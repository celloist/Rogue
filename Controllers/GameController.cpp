//
// Created by alhric on 30-Oct-15.
//

#include "GameController.h"
#include "../Views/GameOutput.h"
#include <sstream>

GameController::GameController(){
    initCommands();
}
//controller functions
void GameController::start(bool testing) {
    int numLevels;
    int numXRooms;
    int numYRooms;

    if (!testing) {
        stringstream(io.askInput("Hoe veel verdiepingen:")) >> numLevels;
        stringstream(io.askInput("Hoe veel kamers over de breedte:")) >> numYRooms;
        stringstream(io.askInput("Hoe veel verdiepingen lengte:")) >> numXRooms;
    } else {
        numLevels = 1;
        numXRooms = 3;
        numYRooms = 3;
    }

    game.setUp(numLevels, numXRooms, numYRooms);
    Level* currentLevel = game.getCurrentLevel();
    GameOutput levelIo;
    while (!gameOver){
//        levelIo.displayLevel(currentLevel);
//        levelIo.displayLevelsMinSpanningTree(currentLevel);
//        levelIo.displayLevelsRoomDistances(currentLevel);

        string command = io.askInput("What da fuck wil je doen? (type help voor suggesties)");
        commandReader(command);
    }
}

void GameController::initCommands() {



   commands["stop"] = GameController::end;
    commands["help"] = GameController::help;

    //while attacking
    commands["vlucht"] = GameController::escape;
    commands["aanval"] = GameController::attack;
    commands["drink drankje"] = GameController::usePotion;
    commands["gebruik object"] = GameController::useItem;

    //while in room
    commands["aanvallen"] = GameController::engage;//TODO
    commands["zoek kamer"] = GameController::searchRoom;
    commands["rust"] = GameController::rest;
    commands["bekijk spullen"] = GameController::checkBag;
    commands["bekijk map"] = GameController::checkMap;
    commands["kenmerken"] = GameController::checkStats;
    commands["kompas"] = GameController::kompas;
    commands["talisman"] = GameController::grenade;
    commands["granaat"] = GameController::talisman;
    //    commands["cheat"] = GameController::cheat;
    commands["save"] = GameController::save;

}


void  GameController::commandReader(string inputCommand) {

    bool check = false;
    auto func = commands[inputCommand];
    if (commands.find(inputCommand) != commands.end() && func != NULL){
        check = true;
    (this->*func)();
   }
        if(!check)
        io.display("Computer says no. Type help for list of commands \n");


}


//both
void GameController::escape() {

}

void GameController::end() {
    io.display("Ending game");
    gameOver = true;

}
void GameController::help() {
    string helpCommands = "commands list: \n";
    for (map<string,command>::iterator it = commands.begin(); it!=commands.end(); ++it)
    {
        helpCommands += (it->first + "\n");
    }
    io.display(helpCommands);

}

void GameController::talisman() {

}
void GameController::kompas() {

}


//in fight
void GameController::attack() {
    set<string> fightcommands{
            ""
    };


}

void GameController::usePotion() {

}

void GameController::useItem() {

}

//in room
void GameController::engage() {

}

void GameController::searchRoom() {

}

void GameController::rest() {

}

void GameController::checkBag() {

}

void GameController::checkMap() {

}

void GameController::checkStats() {

}

void GameController::grenade() {

}

void GameController::save() {

}



