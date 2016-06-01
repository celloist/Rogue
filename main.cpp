#include "Controllers/GameController.h"

using namespace std;

int main() {
    try {

        GameController gc;

        gc.start(true, "D:\\Repos\\Rogue\\Descriptions\\", "\\Rooms\\");
    }
    catch (const exception& e)
    {
        cout << e.what() << '\n';
    }

    return 0;
}