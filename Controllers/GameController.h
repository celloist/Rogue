//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_GAMECONTROLLER_H
#define ROGUE_GAMECONTROLLER_H

#include "iostream"
#include "../Game.h"
#include "../Views/ConsoleInputOutput.h"
#include <map>
#include <functional>


using namespace std;

class GameController {

public:
    //controller functions
    void start(bool testing);
    GameController();


private:
    Game game;
    ConsoleInputOutput io;


    typedef void (GameController::*command)();

    bool gameOver = false;
    map<string, command> commands;

    void initCommands();
    //commands
    void commandReader(string inputCommand);
    //both
    void end();
    void escape();

    //while attacking
    void attack();
    void usePotion();
    void useItem();

    //while in room
    void engage();
    void searchRoom();
    void rest();
    void checkBag();
    void checkMap();
    void checkStats();
    void grenade();
    void kompas();
    void talisman();
    void help();
   // string cheat();
    void save();



};


#endif //ROGUE_GAMECONTROLLER_H
