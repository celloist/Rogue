//
// Created by alhric on 30-Oct-15.
//

#include "GameController.h"
#include "../Views/GameOutput.h"
#include <sstream>
#include <algorithm>

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
    game.itemGenerator();
    Level* currentLevel = game.getCurrentLevel();
    GameOutput levelIo;

    //gameloop
    while (!gameOver){
//        levelIo.displayLevel(currentLevel);
//        levelIo.displayLevelsMinSpanningTree(currentLevel);
//        levelIo.displayLevelsRoomDistances(currentLevel);

        string command = io.askInput("Wat da fuck wil je doen? (type help voor suggesties)");
        commandReader(command);
    }
}

//engage while loop
void GameController::engage() {
    engaging = true;
    vector<string> attackCommands;

    attackCommands.push_back("vlucht");
    attackCommands.push_back("aanval");
    attackCommands.push_back("drink drankje");
    attackCommands.push_back("gebruik object");
    attackCommands.push_back("stop");

    io.display("Tijdens een gevecht kun je deze commandos gebruiken: \n vlucht, aanval, drink drankje, gebruik object, stop");

    while(engaging)
    {
        string input = io.askInput("");
        if(std::find(attackCommands.begin(),attackCommands.end(),input) != attackCommands.end())
        {
            if(input=="stop")
                engaging = false;

            commandReader(input);
        }
        else
        {
            io.display("Computer says no. Tijdens een gevecht kun je deze commandos gebruiken: \n vlucht, aanval, drink drankje, gebruik object, stop");
        }
    }
}

void GameController::initCommands() {
    commands["stop"] = &GameController::end;
    commands["help"] = &GameController::help;

    //while attacking
    commands["vlucht"] = &GameController::escape;
    commands["aanval"] = &GameController::attack;
    commands["drink drankje"] = &GameController::usePotion;
    commands["gebruik object"] = &GameController::useItem;

    //while in room
    commands["verplaatsen"] = &GameController::move;
    commands["aanvallen"] = &GameController::engage;
    commands["zoek kamer"] = &GameController::searchRoom;
    commands["rust"] = &GameController::rest;
    commands["bekijk spullen"] = &GameController::checkBag;
    commands["bekijk map"] = &GameController::checkMap;
    commands["kenmerken"] = &GameController::checkStats;
    commands["kompas"] = &GameController::kompas;
    commands["talisman"] = &GameController::grenade;
    commands["granaat"] = &GameController::talisman;
    //    commands["cheat"] = GameController::cheat;
    commands["save"] = &GameController::save;

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
    io.display("Je heb het gevecht verlaten \n");
    engaging = false;
}

//ends the game loop
void GameController::end() {
    io.display("I'll be back");
    gameOver = true;

}

//prints out all the commands
void GameController::help() {
    string helpCommands = "commands list: \n";
    for (map<string,command>::iterator it = commands.begin(); it!= commands.end(); ++it)
    {
        helpCommands += (it->first + ", ");
    }
    io.display(helpCommands);

}

//in fight
void GameController::attack() {
    if(!hero->alive) {
        io.display("Je bent dood, fijne daaaaaaag!");
        end();
    }
    else{
        auto* enemies = hero->getCurrentRoom()->getEnemies();
        for (auto it = enemies->begin(); it != enemies->end(); it++) {
            if(it.operator*()->alive) {
                io.display(hero->attackTarget(it.operator*()));
                io.display(it.operator*()->attackTarget(hero));
            }
            else{

                delete *it;
                it = enemies->erase(it);
            }
        }
    }

}

void GameController::usePotion() {
    string potion = io.askInput("welke drankje? \n");

    if(hero->usePotion(potion,&io)) {
        io.display(potion+ " gebruikt \n");
    }
    else{
        io.display("Drankje niet gevonden probeer de bekijk spullen commando \n");
    }

}

void GameController::useItem() {
    string item = io.askInput("welke zwaard of harnass? \n");

    if(hero->useItem(item,&io)) {
        io.display(item+ " gebruikt \n");
    }
    else{
        io.display("Object niet gevonden probeer de bekijk spullen commando \n");
    }

}

//in room

void GameController::searchRoom() {
//    for (auto it = allItems.begin(); it != allItems.end(); it++) {
//        Item *bagItem = it.operator*();
//        hero.addItem(bagItem);
//    }
}

void GameController::move() {
    string direction = io.askInput("Richtingen die je kunt gaan zijn noord, oost, zuid en west. \n Welke richting wil je gaan? \n");
    vector<string> directions;
    directions.push_back("noord");
    directions.push_back("zuid");
    directions.push_back("oost");
    directions.push_back("west");

    if(std::find(directions.begin(),directions.end(),direction) != directions.end()) {
        //TODO Mj move algorithm
    }
    else{
        io.display("Computer says no. Richtingen die je kunt gaan zijn noord, oost, zuid, west\n");
    }

}

void GameController::rest() {

}

void GameController::checkBag() {

}

void GameController::checkMap() {

}

void GameController::checkStats() {

}

void GameController::save() {

}

void GameController::grenade() {

}

void GameController::kompas() {

}

void GameController::talisman() {

}


