//
// Created by alhric on 30-Oct-15.
//

#include "GameController.h"
#include "../Views/GameOutput.h"
#include "../Views/DeafultLevelOutput.h"
#include "../Views/CheatLevelOutput.h"
#include <sstream>
#include <fstream>

vector<string> readFile (string textfile) {
    ifstream input_file{textfile};
    string line;
    vector<string> list;

    while (getline(input_file, line)) {
        list.push_back(line);
    }

    return list;
}

GameController::GameController() {
    hero = game.getHero();
    initCommands();
}

//controller functions
void GameController::start(bool testing, string roomPathPrefix) {
    int numLevels;
    int numXRooms;
    int numYRooms;

    if (!testing) {
        stringstream(io.askInput("Hoe veel verdiepingen:")) >> numLevels;
        stringstream(io.askInput("Hoe veel kamers over de breedte:")) >> numYRooms;
        stringstream(io.askInput("Hoe veel verdiepingen lengte:")) >> numXRooms;
    } else {
        numLevels = 2;
        numXRooms = 2;
        numYRooms = 2;
    }

    LevelDescritions ld = {
            readFile(roomPathPrefix + "decorations.txt"),
            readFile(roomPathPrefix + "furniture.txt"),
            readFile(roomPathPrefix + "lightsources.txt"),
            readFile(roomPathPrefix + "sizes.txt"),
            readFile(roomPathPrefix + "sounds.txt"),
            readFile(roomPathPrefix + "tidyness.txt"),
            readFile(roomPathPrefix + "misc.txt")
    };

    game.setUp(numLevels, numXRooms, numYRooms, ld);
    game.itemGenerator();
    Level* currentLevel = game.getCurrentLevel();
    //TODO make starting room random
    game.getHero()->setRoom(currentLevel->getStartRoom());
    io.display(game.getHero()->getCurrentRoom()->getDescription() + "\n");

    //gameloop
    while (!gameOver){
        string command = io.askInput("Wat wil je doen? (type help voor suggesties)");
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
    commands["talisman"] = &GameController::talisman;
    commands["handgranaat"] = &GameController::grenade;
    commands["cheat"] = &GameController::cheat;
    commands["save"] = &GameController::save;

}


void GameController::commandReader(string inputCommand) {

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
    map<string, string> directions;
    directions["noord"] = "north";
    directions["zuid"] = "south";
    directions["oost"] = "east";
    directions["west"] = "west";
    directions["beneden"] = "down";
    directions["boven"] = "up";

    string direction = io.askInput("Richtingen die je kunt gaan zijn noord, oost, zuid, west en boven of beneden in een exitroom. \n Welke richting wil je gaan? \n");


    if(directions.find(direction) != directions.end()) {
        Hero* hero = game.getHero();
        Room* currentRoom = hero->getCurrentRoom();
        Room* travelToRoom = currentRoom->getByEdgeName(directions[direction]);

        if (travelToRoom != nullptr && currentRoom->isConnectedTo(travelToRoom)) {
            hero->setRoom(travelToRoom);
            io.display(travelToRoom->getDescription() + "\n\n");

        } else {
            io.display("Computer says no. De richting is geblokkerd of er bestaat geen kamer in de richting: "+ direction+ ".\n");
        }
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
    Level* currentLevel = game.getCurrentLevel();

    /*GameOutput levelIo;
    levelIo.displayLevel(currentLevel);
    levelIo.displayLevelsMinSpanningTree(currentLevel);
    levelIo.displayLevelsRoomDistances(currentLevel);*/
    DeafultLevelOutput dl;
    dl.displayLevel(currentLevel);
}

void GameController::cheat() {
    CheatLevelOutput clOutput;
    clOutput.displayLevel(game.getCurrentLevel());
}

void GameController::checkStats() {

}

void GameController::save() {

}
//TODO test collapse
void GameController::grenade() {
    Level* currentLevel = game.getCurrentLevel();
    if (currentLevel->getMst()->collapse(10)){
        io.display("De kerker schudt op zijn grondvesten, alle tegenstanders in de kamer zijn verslagen! Een donderend geluid maakt duidelijk dat gedeeltes van de kerker zijn ingestort...");
    } else {
        io.display("Je vreest dat een extra handgranaat een cruciale passage zal blokkeren. Het is beter om deze niet meer te gebruiken op deze verdieping.");
    }
}

void GameController::kompas() {
    Level* currentLevel = game.getCurrentLevel();

    GameOutput levelIo;

    Room* start = game.getHero()->getCurrentRoom();
    Room* exit = currentLevel->getExit();

    levelIo.displayShortestPathToExit(start->getShortestPathToExit(exit), start, exit);
    io.display("\n");
}

void GameController::talisman() {
    Level* currentLevel = game.getCurrentLevel();
    Room* currentRoom = game.getHero()->getCurrentRoom();
    int distance = currentRoom->findRoom(currentLevel->getExit());
    io.display("De talisman licht op en fluistert dat de trap  "+ to_string(distance) +" kamers ver weg is.\n");
}