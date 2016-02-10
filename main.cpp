#include <iostream>
#include "Game.h"
#include "Controllers/GameController.h"

using namespace std;

int main() {
    GameController gc;

    gc.start(true);

    return 0;
}