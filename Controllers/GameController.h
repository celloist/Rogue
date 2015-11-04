//
// Created by alhric on 30-Oct-15.
//

#ifndef ROGUE_GAMECONTROLLER_H
#define ROGUE_GAMECONTROLLER_H

#include "iostream"
#include <map>
#include <functional>


using namespace std;

class GameController {

public:
    GameController();
    void inputReader();

private:

    typedef string (GameController::*command)();
    bool gameOver = false;
    map<std::string,command> commands;

    //commands
    string  commandReader(string* inputCommand);
    void initCommands();
    //both
    string end();
    string escape();

    //while attacking
    string attack();
    string usePotion();
    string useItem();

    //while in room
    string engage();
    string searchRoom();
    string rest();
    string checkBag();
    string checkMap();
    string checkStats();
    string grenade();
    string talisman();
    string help();
   // string cheat();
    string save();



};


#endif //ROGUE_GAMECONTROLLER_H
