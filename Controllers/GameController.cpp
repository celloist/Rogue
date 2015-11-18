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
        numXRooms = 400;
        numYRooms = 400;
    }

    game.setUp(numLevels, numXRooms, numYRooms);
    Level* currentLevel = game.getCurrentLevel();
    GameOutput levelIo;
    currentLevel->calcPrimMinSpanTree();
    while (!gameOver){

        commandReader("stop");
        /*levelIo.displayLevel(currentLevel);
        levelIo.displayLevelsMinSpanningTree(currentLevel);
        levelIo.displayLevelsRoomDistances(currentLevel);*/

        //string command = io.askInput("Wat wil je doen?");
        auto mapData = currentLevel->getNorthEastRoom()->getShortestPathToExit();
        levelIo.displayShortestPathToExit(mapData , currentLevel->getNorthEastRoom(), currentLevel->getExit() );
        break;
        /*string command;
        getline(cin,command);
        cout << commandReader(&command) << endl;*/
    }
}

void GameController::initCommands() {



//   commands["stop"] = (void (*)()) &GameController::end;
//    commands["help"] = &GameController::help;
//
//    //while attacking
//    commands["vlucht"] = &GameController::escape;
//    commands["aanval"] = &GameController::attack;
//    commands["drink drankje"] = &GameController::usePotion;
//    commands["gebruik object"] = &GameController::useItem;
//
//    //while in room
//    commands["aanvallen"] = &GameController::engage;//TODO
//    commands["zoek kamer"] = &GameController::searchRoom;
//    commands["rust"] = &GameController::rest;
//    commands["bekijk spullen"] = &GameController::checkBag;
//    commands["bekijk map"] = &GameController::checkMap;
//    commands["kenmerken"] = &GameController::checkStats;
//    commands["kompas"] = &GameController::kompas;
//    commands["talisman"] = &GameController::grenade;
//    commands["granaat"] = &GameController::talisman;
//    commands["cheat"] = &GameController::cheat;
//    commands["save"] = &GameController::save;

}


void  GameController::commandReader(string inputCommand) {

//    command func = commands[inputCommand];
////    if (commands.find(inputCommand) != commands.end()){
//    (this->*func)();
////    }
    //return "Computer says no. Type help for list of commands";
}


//both
void GameController::escape() {

}

void GameController::end() {
    gameOver = true;

}
void GameController::help() {
    string helpCommands = "commands list: \n";
    /*for (map<string,command>::iterator it = commands.begin(); it!=commands.end(); ++it)
    {
        helpCommands += (it->first + "\n");
    }*/

}

void GameController::talisman() {

}
void GameController::kompas() {

}


//in fight
void GameController::attack() {
    set<string> commands{
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



