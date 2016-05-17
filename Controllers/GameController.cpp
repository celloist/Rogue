//
// Created by alhric on 30-Oct-15.
//

#include "GameController.h"
#include "../Views/GameOutput.h"
#include "../Views/DeafultLevelOutput.h"
#include "../Views/CheatLevelOutput.h"
#include "../Views/ItemVisitor.h"
#include "../Views/ItemDescriptorVisitor.h"

random_device dev;
default_random_engine def_rand {dev()};

GameController::GameController() : game(Hero("Klaas", 2),def_rand) {
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
        numLevels = 2;
        numXRooms = 3;
        numYRooms = 3;
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
    auto enemiesSet = devideSet(readFile(path + "enemies.txt"), ' ');
    game.createEnemiesFromSet(enemiesSet);
    //Items
    auto itemsSet = devideSet(readFile(path + "items.txt"), ' ');
    game.createItemsFromSet(itemsSet);
    //
    auto trapsSet = devideSet(readFile(path + "traps.txt"), ' ');
    game.createTrapsFromSet(trapsSet);

    //set up with all the users params and above items
    game.setUp(numLevels, numXRooms, numYRooms, ld);
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

void GameController::initCommands() {
    commands["stop"] = &GameController::end;
    commands["help"] = &GameController::help;

    //while attacking
    commands["vlucht"] = &GameController::escape;
    commands["aanval"] = &GameController::attack;
    commands["gebruik object"] = &GameController::useItem;

    //while in room
    commands["verplaats"] = &GameController::move;
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
    auto func = commands[inputCommand];
    if (commands.find(inputCommand) != commands.end() && func != NULL) {
        (this->*func)();
    } else {
        io.display("Computer says no. Type help voor commando's \n");
    }
}


//add random
void GameController::escape() {
    io.display("Je heb het gevecht verlaten \n");
    move();
}

//ends the game loop
void GameController::end() {
    io.display("I'll be back \n");
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
    auto enemies = *hero->getCurrentRoom()->getEnemies();

    int numDefeatedEnemies = 0;
    for (auto currentEnemy : enemies) {
        int damageInflicted = hero->attackTarget(currentEnemy);

        //the enemy has been defeated
        if(!currentEnemy->alive) {
            io.display("Je hebt vijand "+ currentEnemy->name + " verslagen!\n");
            hero->exp += currentEnemy->exp * currentEnemy->level;

            int pos = isTopLevelEnemy(currentEnemy);
            if (pos >= 0) {
                topLevelEnemies.erase(topLevelEnemies.begin() + pos);
                if (topLevelEnemies.size() == 0) {
                    io.display("Je hebt alle eind vijanden verslagen, fijne daaaaaaag!\n");
                    end();
                    break;
                }
            }
            numDefeatedEnemies++;
        } else {
            io.display(((damageInflicted > 0) ? "Je hebt "+ currentEnemy->name + " "+ to_string(damageInflicted) + " schade aangericht die houdt nog "+ to_string(currentEnemy->health) +" levenspunten over!"  : "Je hebt "+ currentEnemy->name + " gemist") + "\n" );
            //the enemy fights back
            int damageReceived = currentEnemy->attackTarget(hero);

            io.display( currentEnemy->name + " " + ((damageReceived > 0) ? "heeft jouw "+ to_string(damageReceived) +" schade aangericht" : "heeft jou gemist!") + "\n" );
            if(!hero->alive) {
                io.display("Je bent dood, fijne daaaaaaag!\n");
                end();
                break;
            }
        }

        io.display("\n");
    }

    if (!gameOver) {
        if (numDefeatedEnemies > 0) {
            game.cleanUpEnemies(enemies);
        }
        vector<string> allowedCommands {
                "help",
                "stop",
                "aanval",
                "vlucht"
        };

        while (true) {
            string command = io.askInput("Wil je verder vechten, vluchten of stoppen?");
            if (std::find(allowedCommands.begin(), allowedCommands.end(), command) != allowedCommands.end()) {
                commandReader(command);
                break;
            } else {
                io.display("Commando niet herkend! Toegestane commands zijn:\n");
                for (auto item : allowedCommands) {
                    io.display("- " + item + "\n");
                }
                io.display("\n");
            }
        }
    }
}

void GameController::useItem() {
    auto bag = hero->getBag();
    ItemVisitor itemVisitor;
    ItemDescriptorVisitor descriptor;
    io.display("Je kunt gebruik maken van:\n");
    for (auto it = bag->begin(); it != bag->end(); it++) {
        auto item = it.operator*();
        item->accept(&descriptor);
        io.display("- "+ descriptor.getOutput() + "\n");
    }
    string item = io.askInput("Welke object? \n");

    vector<Item*>::iterator pos = find_if(bag->begin(), bag->end(), [&item] (Item* i) {
        return i->getName() == item;
    });

    if (pos != bag->end()) {
        auto itemVisitable = pos.operator*();
        itemVisitable->use(hero);
        itemVisitable->accept(&itemVisitor);
        io.display(itemVisitor.getOutput() + "\n");

        bag->erase(pos);
        game.removeItem(itemVisitable);

    } else {
        io.display("Item: "+ item  + " niet gevonden!");
    }

    io.display("\n");
}

//TODO verbeteren van gebruik
void GameController::searchRoom() {
    //search room for items and pick them up
    Room* currentRoom = game.getHero()->getCurrentRoom();
    if (currentRoom) {

        if (currentRoom->hasTrap()) {
            io.display("O jee, een val!");
            Trap *trap = currentRoom->getTrap();
            auto message = trap->use(hero);
            if (hero->alive) {
                io.display("Maar je hebt de val net op tijd ontdenkt!\n\n");
            } else {
                io.display("Je bent in de val gestapt en helaas dood! Fijne daaag!\n");
                end();
            }
        }

        if (!gameOver) {
            vector<Item *> *allItems = currentRoom->getItems();
            if (allItems != nullptr && allItems->size() > 0) {

                for (auto it = allItems->begin(); it != allItems->end(); it++) {
                    Item *bagItem = it.operator*();
                    io.display(
                            "Je hebt iets tijdens je zoekttocht iets nieuws aan de kamer ontdekt in de ruimte en toegevoegd aan je buidel, namelijk een " +
                            bagItem->getDescription() + "\n");
                    hero->addItem(bagItem);
                }

                allItems->clear();
            } else {
                io.display("Geen spullen gevonden in kamer!");
            }
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
//TODO implement rest and random attack
void GameController::rest() {
    if (hero->health < 100) {
        //add a random amount of between 5 and 25
        uniform_int_distribution<int> amountHealthAdded{5, 25};
        int healthBefore = hero->health;
        int healthToAdd = amountHealthAdded(dev);
        hero->health = (hero->health + healthToAdd > 100 ? 100 : hero->health + healthToAdd);
        io.display("Het bijkomen heeft je goed gedaan en je hebt "
                   + to_string((hero->health - healthBefore))
                   + "bijgekregen en hebt een totaal van: "
                   + to_string(hero->health) +"! \n");

        //Random attack if any enemies reside in the current room
        if (hero->getCurrentRoom()->getEnemies() != nullptr) {
            uniform_int_distribution<int> dist{1, 6};
            int attackChance = dist(dev);
            //attack?
            if (attackChance == 1) {
                //auto enemies = hero->getCurrentRoom()->getEnemies();
                io.display("Je hoort een geluid en draait net op tijd om te zien dat je wordt aangevallen!\n");
                attack();
            }
        }
    } else {
        io.display("Je hoeft niet bij te komen!\n");
    }
}

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
//TODO display user stats
void GameController::checkStats() {
    io.display("Onze held: "+ hero->name + "\n");
    io.display(" - Aanvalskracht: "+ to_string(hero->attack) + "\n");
    io.display(" - Verdediging: "+ to_string(hero->defence) + "\n");
    io.display(" - Ervaringspunten: "+ to_string(hero->exp) + "\n");
    io.display(" - Levenskracht: "+ to_string(hero->health) + " van 100\n");
    io.display(" - Level: "+ to_string(hero->level) + "\n");
}

void GameController::load() {
    if (hero->getCurrentRoom() == game.getCurrentLevel()->getStartRoom()) {
        vector<Item *> *items = hero->getBag();

        for (auto it = items->begin(); it != items->end(); it++) {
            game.removeItem(it.operator*());
        }

        hero->clearItems();

        auto loadedItems = devideSet(readFile(path + "heroItems.txt"), ' ');
        auto createdItems = game.createItemsFromSet(loadedItems);

        for (auto item : createdItems) {
            hero->addItem(item);
        }
        //load user attributes
        vector<vector<string>> heroAttributes = devideSet(readFile(path + "heroAttributes.txt"), ' ');
        for (auto it = heroAttributes.begin(); it != heroAttributes.end(); it++) {
            auto heroAttributesRow = it.operator*();
            if (heroAttributesRow.size() == 2) {
                //value
                int value = std::atoi(heroAttributesRow.at(1).c_str());
                //Get name
                string name = heroAttributesRow.at(2);

                if (name == "defence") {
                    hero->defence = value;
                } else if (name == "attack") {
                    hero->attack = value;
                } else if (name == "level") {
                    hero->level = value;
                } else if (name == "awareness") {
                    hero->awareness = value;
                } else if (name == "exp") {
                    hero->exp = value;
                }
            }
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
            io.display("Items opgeslagen.\n");
        } else {
            io.display("Fout tijdens het opslaan van de items!\n");
        }

        myfile.open(path + "heroAttributes.txt");
        if (myfile.is_open()) {
            myfile <<  "defence "+      to_string(hero->defence) + "\n";
            myfile <<  "attack "+       to_string(hero->attack) + "\n";
            myfile <<  "awareness "+    to_string(hero->awareness) + "\n";
            myfile <<  "level "+        to_string(hero->level);
            myfile <<  "exp "+        to_string(hero->exp);

            myfile.close();
            io.display("Attributen opgeslagen!\n");
        } else {
            io.display("Fout tijdens het opslaan van de attributen!\n");
        }
    } else {
        io.display("Je kunt alleen bij de uitgangen opslaan!\n");
    }
}

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
                io.display(" - een " + e->name + " met "+ to_string(e->health) +" levenspunten van level "+ to_string(e->level) +";\n");
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