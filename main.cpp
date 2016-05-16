#include "Controllers/GameController.h"

using namespace std;

int main() {
    try {

        GameController gc;

        gc.start(true, "/Users/markjan/ClionProjects/Rogue/Descriptions/", "/Rooms/");
    }
    catch (const exception& e)
    {
        cout << e.what() << '\n';
    }

    return 0;
}