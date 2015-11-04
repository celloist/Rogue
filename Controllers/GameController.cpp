//
// Created by alhric on 30-Oct-15.
//

#include "GameController.h"

GameController::GameController(){
    initCommands();
}

void GameController::inputReader() {

while (!gameOver){
    string x;
    getline(cin,x);
    cout << commandReader(&x) << endl;
    }

}

string  GameController::commandReader(string *inputCommand) {

    for (map<string,command>::iterator it = commands.begin(); it!=commands.end(); ++it)
    {
        if(it->first == *inputCommand)
        {
            auto mem_fun = it->second;
            return (this->*mem_fun)();
        }

    }
   // return commands.find(*inputCommand)->second;
    return "Computer says no. Type help for list of commands";
}

void GameController::initCommands() {


    commands["end"] = &GameController::end;
    commands["help"] = &GameController::help;
    //while attacking
    commands["run"] = &GameController::escape;
    commands["attack"] = &GameController::attack;
    commands["use potion"] = &GameController::usePotion;
    commands["use item"] = &GameController::useItem;

    //while in room
    commands["engage"] = &GameController::engage;//TODO
    commands["search"] = &GameController::searchRoom;
    commands["rest"] = &GameController::rest;
    commands["check bag"] = &GameController::checkBag;
    commands["map"] = &GameController::checkMap;
    commands["stats"] = &GameController::checkStats;
    commands["talisman"] = &GameController::grenade;
    commands["grenade"] = &GameController::talisman;
    commands["cheat"] = &GameController::cheat;
    commands["save"] = &GameController::save;

}



//both
string GameController::escape() {
    return "run";
}
string GameController::end() {
    gameOver = true;
    return "ending game";
}
string GameController::help() {
    string helpCommands = "commands list: \n";
    for (map<string,command>::iterator it = commands.begin(); it!=commands.end(); ++it)
    {
        helpCommands += (it->first + "\n");
    }
    return helpCommands;
}

string GameController::talisman() {
    return "talisman";
}

//in fight
string GameController::attack() {
    return "attack";
}

string GameController::usePotion() {
    return "use potion";
}

string GameController::useItem() {
    return "use item";
}

//in room
string GameController::engage() {
    return "engage";
}

string GameController::searchRoom() {
    return "search room";
}

string GameController::rest() {
    return "rest";
}

string GameController::checkBag() {
    return "check bag";
}

string GameController::checkMap() {
    return "check map";
}

string GameController::checkStats() {
    return "check stats";
}

string GameController::grenade() {
    return "grenade";
}

string GameController::save() {
    return "saving game";
}




