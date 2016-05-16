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

GameController::GameController() : game(Hero("Kloes", 2),def_rand) {
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

    int numDefeatedEnemies = 0;
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
                    io.display("Je hebt alle eind vijanden verslagen, fijne daaaaaaag!\n");
                    end();
                    break;
                }
            }
            numDefeatedEnemies++;
        } else {
            //the enemy fights back
            io.display(currentEnemy->attackTarget(hero));

            if(!hero->alive) {
                io.display("Je bent dood, fijne daaaaaaag!\n");
                end();
                break;
            }
        }

        io.display("\n");
    }

    if (numDefeatedEnemies > 0 && !gameOver) {
        while (numDefeatedEnemies > 0) {
            for (auto it = enemies->begin(); it != enemies->end(); it++) {
                auto currentEnemy = it.operator*();

                if (!currentEnemy->alive) {
                    enemies->erase(it);
                    numDefeatedEnemies--;
                    break;
                }
            }
        }

        game.cleanUpEnemies();
    }
}

void GameController::usePotion() {
    string items = hero->displayInventory(itemType::potion);

    io.display("Drankjes: "+ items + "\n");

    string potion = io.askInput("Welke drankje? \n");

    io.display(hero->usePotion(potion));
}

void GameController::useItem() {
    auto bag = hero->getBag();
    io.display("Je kunt gebruik maken van");
    for (auto it = bag->begin(); it != bag->end(); it++) {
        auto item = it.operator*();
        io.display("Item: "+ item->getDescription() + "\n");
    }
    string item = io.askInput("Welke object? \n");

    vector<Item*>::iterator pos = find_if(bag->begin(), bag->end(), [&item] (Item* i) {
        return i->getName() == item;
    });

    if (pos != bag->end()) {
        io.display(pos.operator*()->use(hero));
        Item* itemToRemove = pos.operator*();
        bag->erase(pos);
        game.removeItem(itemToRemove);

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

        vector<Item *> loadedItems = getItemsFromFile(path + "heroItems.txt");

        for (auto it = loadedItems.begin(); it != loadedItems.end(); it++) {
            game.addItem(it.operator*());
            hero->addItem(it.operator*());
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