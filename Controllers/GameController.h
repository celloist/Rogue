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
    GameController();
    //controller functions
    void start(bool testing, string, string);

private:
    Game game;
    ConsoleInputOutput io;
    //TODO fix the way in which the hero property is added
    Hero* hero;
    string path;


    typedef void (GameController::*command)();

    bool gameOver = false;
    bool engaging = false;
    map<string, command> commands;

    void initCommands();
    void displayRoomDetails();
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
    void move();
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
    void cheat();
    void save();
    void load();
};


#endif //ROGUE_GAMECONTROLLER_H
