//
// Created by alhric on 30-Oct-15.
//

#include "GameController.h"
#include "../Views/GameOutput.h"
#include "../Views/DeafultLevelOutput.h"
#include "../Views/CheatLevelOutput.h"
#include "../Items/Weapon.h"
#include "../Items/Armor.h"
#include "../Items/potion.h"

random_device dev;
default_random_engine def_rand {dev()};


map<int, vector<Enemy*>> getEnemiesFromFile (string path) {
    vector<vector<string>> devidedSetEnemiesDescriptions = devideSet(readFile(path), ' ');
    //Random enemies
    map<int, vector<Enemy*>> enemies;
    for (auto it = devidedSetEnemiesDescriptions.begin(); it != devidedSetEnemiesDescriptions.end(); it++) {

        auto enemiesDescriptionSetRow = it.operator*();
        if (enemiesDescriptionSetRow.size() == 2) {
            //level
            int level = std::atoi(enemiesDescriptionSetRow.at(0).c_str());
            //Get name
            string name = enemiesDescriptionSetRow.at(1);

            Enemy *enemy = new Enemy{name, level,def_rand};

            if (enemies.find(enemy->level) == enemies.end()) {
                enemies[enemy->level] = vector<Enemy*>{};
            }

            enemies[enemy->level].push_back(enemy);

        }
    }

    return enemies;
}

vector<Item*> getItemsFromFile (string path) {
    vector<Item*> items;
    vector<vector<string>> devidedSetItemsDescriptions = devideSet(readFile(path), ' ');

    for (auto it = devidedSetItemsDescriptions.begin(); it != devidedSetItemsDescriptions.end(); it++) {
        auto values = it.operator*();

        int type = atoi(values.at(0).c_str());

        string name = values.at(1);
        int value = atoi(values.at(2).c_str());

        if (type == itemType::weapon) {
            items.push_back(new Weapon{name, itemType::weapon, value});
        } else if (type == itemType::armor) {
            items.push_back(new Armor{name, itemType::armor, value});
        } else if (type == itemType::potion) {
            items.push_back(new Potion{name, itemType::potion, value});
        } else if (type == itemType::trap){
            items.push_back(new Trap{name, itemType::trap, value});
        }
    }

    return items;

}


GameController::GameController() : game(Hero("Kloes", 500),def_rand) {
    hero = game.getHero();
    initCommands();
}

//controller functions
void GameController::start(bool testing, string pathPrefix, string roomPrefix) {
    int numLevels;
    int numXRooms;
    int numYRooms;

    path = pathPrefix;

    if (!testing) {
        stringstream(io.askInput("Hoe veel verdiepingen:")) >> numLevels;
        stringstream(io.askInput("Hoe veel kamers over de breedte:")) >> numYRooms;
        stringstream(io.askInput("Hoe veel verdiepingen lengte:")) >> numXRooms;
    } else {
        numLevels = 3;
        numXRooms = 4;
        numYRooms = 4;
    }

    string roomPathPrefix = pathPrefix + roomPrefix;
    //Room level descriptions
    LevelDescritions ld = {
            readFile(roomPathPrefix + "decorations.txt"),
            readFile(roomPathPrefix + "furniture.txt"),
            readFile(roomPathPrefix + "lightsources.txt"),
            readFile(roomPathPrefix + "sizes.txt"),
            readFile(roomPathPrefix + "sounds.txt"),
            readFile(roomPathPrefix + "tidyness.txt"),
            readFile(roomPathPrefix + "misc.txt")
    };
    //enemies, items and traps
    map<int, vector<Enemy*>> enemies = getEnemiesFromFile(path + "enemies.txt");
    vector<Item*> items = getItemsFromFile(path + "items.txt");
    vector<Item*> traps = getItemsFromFile(path + "traps.txt");

    //set up with all the users params and above items
    game.setUp(numLevels, numXRooms, numYRooms, ld, enemies, items, traps);
    //set the current room
    Level* currentLevel = game.getCurrentLevel();
    game.getHero()->setRoom(currentLevel->getStartRoom());

    //Display the startroom details
    displayRoomDetails();

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
        if(std::find(attackCommands.begin(),attackCommands.end(),input) != attackCommands.end()) {
            if(input=="stop")
                engaging = false;

            commandReader(input);
        } else {
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
    commands["load"] = &GameController::load;
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

    auto* enemies = hero->getCurrentRoom()->getEnemies();
    for (auto it = enemies->begin(); it != enemies->end(); it++) {
        auto currentEnemy = it.operator*();

        io.display(hero->attackTarget(currentEnemy));
        //the enemy has been defeated
        if(!currentEnemy->alive) {
            hero->exp += currentEnemy->exp;

            int pos = isTopLevelEnemy(currentEnemy);
            if (pos >= 0) {
                topLevelEnemies.erase(topLevelEnemies.begin() + pos);
                if (topLevelEnemies.size() == 0) {
                    io.display("Je hebt alle eind vijanden verslagen, fijne daaaaaaag!");
                    end();
                }
            }
            it = enemies->erase(it);
        } else {
            //the enemy fights back
            io.display(currentEnemy->attackTarget(hero));

            if(!hero->alive) {
                io.display("Je bent dood, fijne daaaaaaag!");
                end();
            }
        }
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

//TODO verbeteren van gebruik
void GameController::searchRoom() {
    //search room for items and pick them up
    Room* currentRoom = game.getHero()->getCurrentRoom();
    if (currentRoom) {

        if (currentRoom->hasTrap()) {
            io.display("O jee, een val!");
            Trap* trap = currentRoom->getTrap();
            auto message = trap->use(hero);
            if (hero->alive){
                io.display("Maar je hebt de val net op tijd ontdenkt!");
            } else {
                io.display("Je bent in de val gestapt en helaas dood! Fijne daaag!");
                end();
            }
        }

        vector<Item*>* allItems = currentRoom->getItems();
        if (allItems != nullptr && allItems->size() > 0) {

            for (auto it = allItems->begin(); it != allItems->end(); it++) {
                Item *bagItem = it.operator*();
                io.display("Je hebt iets tijdens je zoekttocht iets nieuws aan de kamer ontdekt in de ruimte, namelijk een "+ bagItem->getName() + "\n");
                hero->addItem(bagItem);
            }
        } else {
            io.display("Geen spullen gevonden in kamer!");
        }
    }
}

void GameController::move() {
    map<string, string> directions;
    //direction translations
    directions["noord"] = "north";
    directions["zuid"] = "south";
    directions["oost"] = "east";
    directions["west"] = "west";
    directions["beneden"] = "down";
    directions["boven"] = "up";

    vector<string> availibleDirectionsRefrence;

    Hero* hero = game.getHero();
    Room* currentRoom = hero->getCurrentRoom();
    string avalibleDirections = "";
    //check avialible directions by testing each direction
    for (auto it = directions.begin(); it != directions.end(); it++) {
        Room* r = currentRoom->getByEdgeName(it->second);
        if (r != nullptr && currentRoom->isConnectedTo(r)) {
            availibleDirectionsRefrence.push_back(it->first);
            avalibleDirections+= ((avalibleDirections.length() == 0) ? "" : ", ") + it->first;
        }
    }

    string direction = io.askInput("Richtingen die je kunt gaan zijn "+ avalibleDirections +". \n Welke richting wil je gaan? \n");
    //check if the direction is in the availible directions, otherwise display an error message
    if(find(availibleDirectionsRefrence.begin(), availibleDirectionsRefrence.end(), direction) != availibleDirectionsRefrence.end()) {
        Room* travelToRoom = currentRoom->getByEdgeName(directions[direction]);
        hero->setRoom(travelToRoom);
        //display the current room details
        displayRoomDetails();
    }
    else{
        io.display("Computer says no. Richtingen bestaat niet of is geblokkeerd!\n");
    }

}

void GameController::rest() {}

void GameController::checkBag() {
    string inventory = hero->displayInventory();
    io.display("Buidel: "+ inventory +"\n");
}

void GameController::checkMap() {
    Level* currentLevel = game.getCurrentLevel();
    DeafultLevelOutput dl;
    dl.displayLevel(currentLevel);
}

void GameController::cheat() {
    CheatLevelOutput clOutput;
    clOutput.displayLevel(game.getCurrentLevel());
}

void GameController::checkStats() {}

void GameController::load() {
    if (hero->getCurrentRoom() == game.getCurrentLevel()->getStartRoom()) {
        vector<Item *> *items = hero->getBag();

        for (auto it = items->begin(); it != items->end(); it++) {
            game.removeItem(it.operator*());
        }

        hero->clearItems();

        vector<Item *> loadedItems = getItemsFromFile(path + "heroItems.txt");

        for (auto it = loadedItems.begin(); it != loadedItems.end(); it++) {
            game.addItem(it.operator*());
            hero->addItem(it.operator*());
        }
    } else {
        io.display("Je kunt alleen in de startkamer laden!");
    }
}

void GameController::save() {

    if (hero->getCurrentRoom() == game.getCurrentLevel()->getExit()) {
        vector<Item *> *items = hero->getBag();
        ofstream myfile;
        myfile.open(path + "heroItems.txt");
        if (myfile.is_open()) {
            for (auto it = items->begin(); it != items->end(); it++) {
                Item *item = it.operator*();
                myfile << to_string(item->getType()) + " " + item->getName() + " " + to_string(item->getValue()) + "\n";
            }

            myfile.close();
            io.display("Opgeslagen");
        } else {
            io.display("Fout tijdens het opslaan!");
        }
    } else {
        io.display("Je kunt alleen bij de uitgangen opslaan!");
    }
}
//TODO test collapse
void GameController::grenade() {
    Level* currentLevel = game.getCurrentLevel();
    bool collapsed = currentLevel->getMst()->collapse(10);
    if (collapsed){
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

void GameController::displayRoomDetails() {
    Room* currentRoom = game.getHero()->getCurrentRoom();
    if (currentRoom) {
        io.display(currentRoom->getDescription() + "\n");
        vector<Enemy*>* enemies = currentRoom->getEnemies();
        if (enemies != nullptr && enemies->size() > 0) {
            io.display("\nAanwezig:\n");

            for (auto it = enemies->begin(); it != enemies->end(); it++) {
                Enemy* e = it.operator*();
                io.display(" - een " + e->name + " met "+ to_string(e->health) +" levenspunten;\n");
            }

            io.display("\n");
        }
    }
}

int GameController::isTopLevelEnemy(Enemy *enemy) {
    //Not initialized yet
    if (topLevelEnemies.size() == 0) {
        auto allEnemies = game.getEnemies();

        for (auto it = allEnemies->begin(); it != allEnemies->end(); it++) {
            if (it.operator*()->level >= 10){
                topLevelEnemies.push_back(it.operator*());
            }
        }
    }

    int i = 0;
    for (auto it = topLevelEnemies.begin(); it != topLevelEnemies.end(); it++, i++) {
        if (enemy == it.operator*()) {
            return i;
        }
    }

    return -1;
}
