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

    bool calculated = currentLevel->getMst()->calc();
    currentLevel->getMst()->collapse(20);
    //gameloop
    while (!gameOver){
        //levelIo.displayLevel(currentLevel);
        levelIo.displayLevelsMinSpanningTree(currentLevel);
        levelIo.displayLevelsRoomDistances(currentLevel);
        Room* start = currentLevel->getNorthEastRoom();
        Room* exit = currentLevel->getExit();

        /*levelIo.displayShortestPathToExit(start->getShortestPathToExit(), start, exit);*/
        string command = io.askInput("Wat da fuck wil je doen? (type help voor suggesties)");
        commandReader(command);
    }
}

//engage while loop
void GameController::engage() {
    engaging = true;
    vector<string> attackCommands;

    attackCommands.push_back("vlucht");//set engaging to false
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
    commands["verplaats"] = &GameController::move;
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
        io.display("Computer says no. Type help voor commando's \n");
}


//add random
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

//TODO delete fixed needs test
void GameController::attack() {
    if(!hero->alive) {
        io.display("Je bent dood, fijne daaaaaaag!");
        end();
    }
    else{
        auto* enemies = hero->getCurrentRoom()->getEnemies();
        int expEarned = 0;
        for (auto it = enemies->begin(); it != enemies->end(); it++) {
            if(it.operator*()->alive) {
                io.display(hero->attackTarget(it.operator*()));
                io.display(it.operator*()->attackTarget(hero));
            }
            else{
                expEarned += it.operator*()->exp;
                it = enemies->erase(it);
                game.cleanUp();
            }
        }
        enemies->clear();
    }

}

void GameController::usePotion() {
    string items = hero->displayInventory(itemType::potion);

    io.display("Drankjes: "+items + "\n");

    string potion = io.askInput("Welke drankje? \n");

   io.display(hero->usePotion(potion));

}

void GameController::useItem() {
    string items = hero->displayInventory(itemType::weapon);

    io.display("Objecten: "+items + "\n");

    string item = io.askInput("Welke zwaard of harnass? \n");

    io.display(hero->useItem(item));

}

//in room

void GameController::searchRoom() {
//    for (auto it = allItems.begin(); it != allItems.end(); it++) {
//        Item *bagItem = it.operator*();
//        hero.addItem(bagItem);
    //
//    }
}

void GameController::move() {
    string direction = io.askInput("Richtingen die je kunt gaan zijn noord, oost, zuid, west en boven of beneden in een exitroom. \n Welke richting wil je gaan? \n");
    vector<string> directions;
    directions.push_back("noord");
    directions.push_back("zuid");
    directions.push_back("oost");
    directions.push_back("west");
    directions.push_back("beneden");
    directions.push_back("boven");

    if(std::find(directions.begin(),directions.end(),direction) != directions.end()) {
        //TODO Mj move algorithm
    }
    else{
        io.display("Computer says no. Richtingen die je kunt gaan zijn noord, oost, zuid, west en boven of beneden in een exitroom\n");
    }

}

void GameController::rest() {

}

void GameController::checkBag() {
    string inventory = hero->displayInventory();
    io.display("Buidel: "+ inventory +"\n");
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


